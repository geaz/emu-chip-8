#include <algorithm>
#include "window.h"

// Init Window Pointer for OpenGL callbacks
Window* Window::windowPointer = NULL;

Window::Window(const char* title, const int width, const int height) : width(width), height(height)
{
    // Store Pointer for OpenGL callbacks
    windowPointer = this;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(window == NULL)
    {
        glfwTerminate();
        throw "Failed to create GLFW window";
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, 
        [](GLFWwindow *window, int width, int height) 
        { 
            glViewport(0, 0, width, height); 
            Window::windowPointer->resize(width, height);
        });
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        throw "Failed to initialize OpenGL context";
    }
}

const void Window::setClearColor(const GLfloat red, const GLfloat green, const GLfloat blue, const GLfloat alpha)
{
    glClearColor(red, green, blue, alpha);
}

const void Window::startLoop()
{
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        for(Screen* screen : screenVec)
        {
            screen->render();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    glfwTerminate();
}

bool Window::addRowDefinition(const GridDefinition rowDefinition)
{
    bool result = true;
    for(GridDefinition existingDef : rowDefinitionVec)
    {
        if(existingDef.index == rowDefinition.index)
        {
            result = false;
            std::cout << "WARN::WINDOW::ROWINDEX_ALREADY_DEFINED";   
            break;
        }
    }
    if(result) rowDefinitionVec.push_back(rowDefinition);
    std::sort(rowDefinitionVec.begin(), rowDefinitionVec.end());

    return result;
}

bool Window::addColumnDefinition(const GridDefinition columnDefinition)
{
    bool result = true;
    for(GridDefinition existingDef : columnDefinitionVec)
    {
        if(existingDef.index == columnDefinition.index)
        {
            result = false;
            std::cout << "WARN::WINDOW::COLUMNINDEX_ALREADY_DEFINED";   
            break;
        }
    }
    if(result) columnDefinitionVec.push_back(columnDefinition);
    std::sort(columnDefinitionVec.begin(), columnDefinitionVec.end());

    return result;
}

bool Window::addScreen(Screen* screen)
{
    bool result = true;
    
    for(Screen* registeredScreen : screenVec)
    {
        if(registeredScreen->row == screen->row
        && registeredScreen->column == screen->column)
        {
            result = false;
            std::cout << "WARN::WINDOW::ROW_COLUMN_TAKEN";    
            break;
        }

        if(screen->column >= (int) columnDefinitionVec.size()
        || screen->row >= (int) rowDefinitionVec.size())
        {
            result = false;
            std::cout << "WARN::WINDOW::ROW_OR_COLUMN_NOT_DEFINED";    
            break;
        }
    }
    screenVec.push_back(screen);        
    resize();

    return result;
}

void Window::resize(const int newWidth, const int newHeight)
{
    width = newWidth;
    height = newHeight;
    resize();
}

const void Window::resize()
{   
    float onePercentageWidth = width / 100.0f;
    float onePercentageHeight = height / 100.0f;

    float rowStartY = 0;
    for(int rowIndex = 0; rowIndex < (int) rowDefinitionVec.size(); rowIndex++)
    {
        GridDefinition rowDefinition = rowDefinitionVec.at(rowIndex);
        float rowHeight = rowDefinition.sizePercentage * onePercentageHeight;

        float columnStartX = 0;
        std::vector<Screen*> rowScreenVec = getScreensInRow(rowIndex);
        for(int colIndex = 0; colIndex < (int) rowScreenVec.size(); colIndex++)
        {
            GridDefinition columnDefinition = columnDefinitionVec.at(colIndex);
            float columnWidth = columnDefinition.sizePercentage * onePercentageWidth;
            
            if(colIndex == (int) rowScreenVec.size() - 1 && columnWidth + columnStartX < width)
            {
                columnWidth = width - columnStartX;
            }

            rowScreenVec.at(colIndex)->setCorrectionValues(width / 2, height / 2);
            rowScreenVec.at(colIndex)->setScreenCords(columnStartX, rowStartY, columnStartX + columnWidth, rowStartY + rowHeight);
            columnStartX += columnWidth;
        }        
        rowStartY += rowHeight;
    }
}

const std::vector<Screen*> Window::getScreensInRow(const int row)
{
    std::vector<Screen*> screensInRow;
    for(Screen* registeredScreen : screenVec)
    {
        if(registeredScreen->row == row)
        {
            screensInRow.push_back(registeredScreen);
        }
    }

    auto columnCompare = [](Screen *s, Screen *s2) { return s->column < s2->column; };
    std::sort(screensInRow.begin(), screensInRow.end(), columnCompare);    

    return screensInRow;
}