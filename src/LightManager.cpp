#include <LightManager.h>

LightManager::LightManager(const std::vector<DirectionalLight>& directionals, const std::vector<PointLight>& points, const std::vector<Spotlight>& spots)
    : directionals(directionals), points(points), spots(spots) {

        // Create directionalShadowMaps
        glGenTextures(1, &directionalShadowMaps);
        glBindTexture(GL_TEXTURE_2D_ARRAY, directionalShadowMaps);
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT16, DIRECTIONAL_SHADOW_SIZE, DIRECTIONAL_SHADOW_SIZE, directionals.size(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_NONE);

        // Directional light FBOs
        for (GLuint i = 0; i < directionals.size(); i++) {
            glBindFramebuffer(GL_FRAMEBUFFER, directionals[i].getDepthMapFBO());
            glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, directionalShadowMaps, 0, i);
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        // Create spotShadowMaps
        glGenTextures(1, &spotShadowMaps);
        glBindTexture(GL_TEXTURE_2D_ARRAY, spotShadowMaps);
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT16, SPOT_SHADOW_SIZE, SPOT_SHADOW_SIZE, spots.size(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_NONE);

        // Spotlights FBOs
        for (GLuint i = 0; i < spots.size(); i++) {
            glBindFramebuffer(GL_FRAMEBUFFER, spots[i].getDepthMapFBO());
            glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, spotShadowMaps, 0, i);
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

}

void LightManager::draw(Model& model, Shader& shader) {
    
    // Minimise peter-panning
    glCullFace(GL_FRONT);

    // Draw meshes
    for (GLsizei meshIndex = 0; meshIndex < model.getMeshCount(); meshIndex++) {
 
        glViewport(0, 0, DIRECTIONAL_SHADOW_SIZE, DIRECTIONAL_SHADOW_SIZE);

        static const std::string locTrans = "localTransform";
        shader.setMat4(locTrans, model.getLocalTransform());

        glBindVertexArray(model.getMesh(meshIndex).getVAO());

        // Render directional shadows
        static const std::string ligProjView = "lightProjView";
        for (GLuint lightIndex = 0; lightIndex < directionals.size(); lightIndex++) {
            DirectionalLight& light = directionals.at(lightIndex);
            glBindFramebuffer(GL_FRAMEBUFFER, light.getDepthMapFBO());
            shader.setMat4(ligProjView, light.getProjView());

            glDrawElementsInstanced(GL_TRIANGLES, model.getMesh(meshIndex).getVertexCount(), GL_UNSIGNED_INT, 0, model.getInstanceCount());
        }
        
        glViewport(0, 0, SPOT_SHADOW_SIZE, SPOT_SHADOW_SIZE);

        // Render spot shadows
        for (GLuint lightIndex = 0; lightIndex < spots.size(); lightIndex++) {
            Spotlight& light = spots.at(lightIndex);
            glBindFramebuffer(GL_FRAMEBUFFER, light.getDepthMapFBO());
            shader.setMat4(ligProjView, light.getProjView());

            glDrawElementsInstanced(GL_TRIANGLES, model.getMesh(meshIndex).getVertexCount(), GL_UNSIGNED_INT, 0, model.getInstanceCount());
        }
    }

    glCullFace(GL_BACK);
    glBindVertexArray(0);
}

void LightManager::clear() {

    for (GLuint i = 0; i < directionals.size(); i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, directionals.at(i).getDepthMapFBO());
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    for (GLuint i = 0; i < spots.size(); i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, spots.at(i).getDepthMapFBO());
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void LightManager::updateUniforms(Shader& shader) {

    glActiveTexture(GL_TEXTURE14);
    glBindTexture(GL_TEXTURE_2D_ARRAY, directionalShadowMaps);
    shader.setInt("directionalShadowMaps", 14);

    glActiveTexture(GL_TEXTURE15);
    glBindTexture(GL_TEXTURE_2D_ARRAY, spotShadowMaps);
    shader.setInt("spotShadowMaps", 15);

    // Directional
    for (GLuint i = 0; i < directionals.size(); i++) {
        const DirectionalLight& light = directionals.at(i);
        shader.setVec3(("directionalLights[" + std::to_string(i) + "].direction").c_str(), light.getDirection());
        shader.setVec3(("directionalLights[" + std::to_string(i) + "].color").c_str(), light.getColor());
        shader.setMat4(("directionalProjViews[" + std::to_string(i) + "]").c_str(), light.getProjView());
    }

    for (GLuint i = 0; i < spots.size(); i++) {
        const Spotlight& light = spots.at(i);
        shader.setVec3(("spotlights[" + std::to_string(i) + "].position").c_str(), light.getPosition());
        shader.setVec3(("spotlights[" + std::to_string(i) + "].direction").c_str(), light.getDirection());
        shader.setVec3(("spotlights[" + std::to_string(i) + "].color").c_str(), light.getColor());
        shader.setMat4(("spotProjViews[" + std::to_string(i) + "]").c_str(), light.getProjView());

        shader.setFloat(("spotlights[" + std::to_string(i) + "].cutOff").c_str(), light.getCutOff());
        shader.setFloat(("spotlights[" + std::to_string(i) + "].constant").c_str(), light.getConstant());
        shader.setFloat(("spotlights[" + std::to_string(i) + "].linear").c_str(), light.getLinear());
        shader.setFloat(("spotlights[" + std::to_string(i) + "].quadratic").c_str(), light.getQuadratic());
    }

    for (GLuint i = 0; i < points.size(); i++) {
        const PointLight light = points.at(i);
        shader.setVec3(("pointLights[" + std::to_string(i) + "].position").c_str(), light.getPosition());
        shader.setVec3(("pointLights[" + std::to_string(i) + "].color").c_str(), light.getColor());
        
        shader.setFloat(("pointLights[" + std::to_string(i) + "].constant").c_str(), light.getConstant());
        shader.setFloat(("pointLights[" + std::to_string(i) + "].linear").c_str(), light.getLinear());
        shader.setFloat(("pointLights[" + std::to_string(i) + "].quadratic").c_str(), light.getQuadratic());
    }
}
