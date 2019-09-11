#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <string>
#include <fstream>
#include <gtc/matrix_transform.hpp>

#include "resource_manager.h"
#include "shader.h"
#include "font.h"
#include "structs.h"

class Screen {
   public:

      Screen(int row,  int column) : row(row), column(column),
           screenShader("shaders\\screen.vshader", "shaders\\screen.fshader")
      {          
         glGenVertexArrays(1, &VAO);
         glGenBuffers(1, &VBO);
         glGenBuffers(1, &EBO);

         setClearColor({ 0, 0, 0, 255});
      }

      void render()
      {        
         drawBackground();
         draw();
      }

      void drawText(float x, float y, std::string text, Color color)
      {
         Font font = ResourceManager::LoadFont("Minecraft", "Minecraft.ttf");
         font.renderText(x + startX, y + startY, text.c_str(), color);
      }      

      void drawRect(float vertices[], unsigned int indices[], int sizeofVertices, int sizeofIndices, Shader shader)
      {
         glBindVertexArray(VAO);

         glBindBuffer(GL_ARRAY_BUFFER, VBO);
         glBufferData(GL_ARRAY_BUFFER, sizeofVertices, vertices, GL_STATIC_DRAW);

         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
         glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofIndices, indices, GL_STATIC_DRAW);

         glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
         glEnableVertexAttribArray(0);
         
         auto projection = glm::ortho(
            0.0f,         
            static_cast<GLfloat>(ResourceManager::ViewportWidth), 
            static_cast<GLfloat>(ResourceManager::ViewportHeight), 
            0.0f);
         screenShader.use();
         screenShader.setMatrix4("projection", projection);
         
         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
         glBindBuffer(GL_ARRAY_BUFFER, 0);
         glBindVertexArray(0);
      }

      void setClearColor(Color color)
      {
         screenShader.setVec4("clearColor", color.red / 255.0f, color.green  / 255.0f, color.blue  / 255.0f, color.alpha  / 255.0f);
      }

      void setScreenCords(const float newStartX, const float newStartY, const float newEndX, const float newEndY)
      {
         startX = newStartX;
         startY = newStartY;
         endX = newEndX;
         endY = newEndY;
      }

      virtual void handleKeys(const int key, const int scancode, const int action, const int mods) {};
      virtual void draw() = 0;

      int row, column;

   private:
      void drawBackground()
      {
         float vertices[] = {
            startX, startY,   // top left
            endX, startY,     // top right
            endX, endY,       // bottom right
            startX, endY,     // bottom left 
         };
         unsigned int indices[] = {
            0, 1, 2,
            0, 3, 2
         };
         drawRect(vertices, indices, sizeof(vertices), sizeof(indices), screenShader);
      }

      Shader screenShader;
      unsigned int VBO, VAO, EBO;
      float startX, startY, endX, endY; 
};

#endif // SCREEN_H