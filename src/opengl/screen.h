#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include <vector>

#include "shader.h"
#include "font.h"
#include "structs.h"

class Screen {
   public:
      Screen(int row,  int column) : row(row), column(column),
           screenShader("shaders\\screen.vshader", "shaders\\screen.fshader")
      { 
         setClearColor({ 0, 0, 0, 255});;
      }

      void render()
      {        
         drawBackground();
         draw();
      }

      void drawText(char* text, Font font, int size)
      {

      }

      void drawRect(float vertices[], unsigned int indices[], int sizeofVertices, int sizeofIndices, Shader shader)
      {
         unsigned int VBO, VAO, EBO;
         glGenVertexArrays(1, &VAO);
         glGenBuffers(1, &VBO);
         glGenBuffers(1, &EBO);

         glBindVertexArray(VAO);

         glBindBuffer(GL_ARRAY_BUFFER, VBO);
         glBufferData(GL_ARRAY_BUFFER, sizeofVertices, vertices, GL_STATIC_DRAW);

         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
         glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofIndices, indices, GL_STATIC_DRAW);

         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
         glEnableVertexAttribArray(0);
         
         shader.use();
         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      }
      
      float getGLWindowCordX(float cord)
      {
         return (cord + startX - widthCorrection) / widthCorrection;
      }

      float getGLWindowCordY(float cord)
      {
         // Top Left Screen should be (0,0) and higher Y = bottom screen
         // Thats why we multiply the result with -1
         return (cord + startY - heightCorrection) / heightCorrection * -1;
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

      void setCorrectionValues(const int newWidthCorrection, const int newHeightCorrection)
      {
         widthCorrection = newWidthCorrection;
         heightCorrection = newHeightCorrection;
      }

      virtual void draw() = 0;

      int row, column;


      private:
         void drawBackground()
         {
            float vertices[] = {
               getGLWindowCordX(0), getGLWindowCordY(0), 0.0f,       // top left
               getGLWindowCordX(endX), getGLWindowCordY(0), 0.0f,    // top right
               getGLWindowCordX(endX), getGLWindowCordY(endY), 0.0f, // bottom right
               getGLWindowCordX(0), getGLWindowCordY(endY), 0.0f     // bottom left 
            };
            unsigned int indices[] = {
               0, 1, 2,
               0, 3, 2
            };
            drawRect(vertices, indices, sizeof(vertices), sizeof(indices), screenShader);
         }

         Shader screenShader;
         float startX, startY, endX, endY; 
         int widthCorrection, heightCorrection;
};

#endif // SCREEN_H