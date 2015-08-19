#include "Drawable.hpp"

Drawable::Drawable(Mesh& mesh, ShaderProgram& shader) : mesh(&mesh), shader(&shader) {

    mesh.linkToShader(getShaderProgram());

    setPosition(glm::vec3(0, 0, 0));

}

Mesh& Drawable::getMesh() {
    return *mesh;
}

glm::vec3 Drawable::getPosition() {
    return position;
}

glm::vec3 Drawable::getRotationInGlobalCoordinates() {
    return rotation_in_global_coordinates;
}

void Drawable::setPosition(glm::vec3 position) {
    this->position = position;
}

void Drawable::setRotationInGlobalCoordinates(glm::vec3 rotation_in_global_coordinates) {
    this->rotation_in_global_coordinates = rotation_in_global_coordinates;
}

ShaderProgram& Drawable::getShaderProgram() {
    return *shader;
}

void Drawable::draw(Camera& camera) {
    getMesh().prepareToBeDrawn();

    getShaderProgram().use();

    glm::mat4 model = calculateModelMatrix();
    GLint model_uniform = getShaderProgram().getUniformLocation( "model");
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 view = camera.getViewMatrix();
    GLint view_uniform = getShaderProgram().getUniformLocation("view");
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = camera.getProjectionMatrix();
    GLint proj_uniform = getShaderProgram().getUniformLocation("proj");
    glUniformMatrix4fv(proj_uniform, 1, GL_FALSE, glm::value_ptr(proj));

    getMesh().draw();
}

void Drawable::moveByGlobal(glm::vec3 move_vector) {
    setPosition(getPosition() + move_vector);
}

void Drawable::rotateByGlobal(glm::vec3 rotation_vector) {
    setRotationInGlobalCoordinates(getRotationInGlobalCoordinates() + rotation_vector);
}

glm::mat4 Drawable::calculateModelMatrix() {
    return calculateTranslationMatrix() * calculateRotationMatrix();
}

glm::mat4 Drawable::calculateRotationMatrix() {
   // Rotate the model about each axis.
   float cx = cos(getRotationInGlobalCoordinates().x);
   float sx = sin(getRotationInGlobalCoordinates().x);

   float cy = cos(getRotationInGlobalCoordinates().y);
   float sy = sin(getRotationInGlobalCoordinates().y);

   float cz = cos(getRotationInGlobalCoordinates().z);
   float sz = sin(getRotationInGlobalCoordinates().z);

   glm::mat4 rotation_z = glm::mat4( cz, -sz, 0, 0,
                                     sz,  cz, 0, 0,
                                     0 ,  0 , 1, 0,
                                     0 ,  0 , 0, 1);

   glm::mat4 rotation_x = glm::mat4( 1, 0 ,  0 , 0,
                                     0, cx, -sx, 0,
                                     0, sx,  cx, 0,
                                     0, 0 ,  0 , 1);

   glm::mat4 rotation_y = glm::mat4(  cy,  0, -sy, 0,
                                      0 ,  1,  0 , 0,
                                      sy,  0,  cy, 0,
                                      0 ,  0,  0 , 1);

   // The convention followed is rotate around X-axis, then Y-axis, and finally Z-axis.
   glm::mat4 rotation_matrix;
   rotation_matrix = rotation_x * rotation_matrix;
   rotation_matrix = rotation_y * rotation_matrix;
   rotation_matrix = rotation_z * rotation_matrix;

   return rotation_matrix;
}

glm::mat4 Drawable::calculateTranslationMatrix() {
    return glm::translate(glm::mat4(), position);
}
