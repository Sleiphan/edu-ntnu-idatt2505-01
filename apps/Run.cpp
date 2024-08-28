#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Example_library/shader_loader.hpp>

void error_callback(int error_code, const char *description)
{
    printf("ERROR: %s", description);
}

int initOpenGL()
{
    glfwSetErrorCallback(error_callback);

    int err_code = glfwInit();
    if (!err_code)
        fprintf(stderr, "ERROR: could not start GLFW3\n");

    return err_code;
}

void print_monitor_stats_just_for_fun()
{
    int monitor_count;
    GLFWmonitor **monitors = glfwGetMonitors(&monitor_count);

    if (!monitors)
        return;

    for (GLFWmonitor *monitor = monitors[0]; monitor_count--; monitors++)
    {
        int monitor_width, monitor_height;
        float monitor_xscale, monitor_yscale;
        glfwGetMonitorPhysicalSize(monitor, &monitor_width, &monitor_height);
        glfwGetMonitorContentScale(monitor, &monitor_xscale, &monitor_yscale);

        printf("[%s]\n - Main monitor width : %d\n - Main monitor height: %d\n - Main monitor xscale: %f\n - Main monitor yscale: %f\n", glfwGetMonitorName(monitor), monitor_width, monitor_height, monitor_xscale, monitor_yscale);
    }
}

GLFWwindow *create_window()
{
    glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    GLFWwindow *window = glfwCreateWindow(720, 480, "Hello OpenGL!", NULL, NULL);

    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
    }

    return window;
}

GLuint register_simple_triangle()
{
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,
        -1.0f,
        0.0f,
        1.0f,
        -1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
    };

    // This will identify our vertex buffer
    GLuint vertex_buffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertex_buffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    return vertex_buffer;
}

int main()
{
    if (!initOpenGL())
        return 1;

    print_monitor_stats_just_for_fun();
    GLFWwindow *window = create_window();

    if (!window)
        return -1;

    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental = true;        // Needed in core profile
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    GLuint vertex_buffer = register_simple_triangle();
    GLuint programID = load_shaders("./shaders/simple_triangle.vert", "./shaders/simple_triangle.frag");

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0, 0, 0, 1);

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and the depth buffer
                                                            // 1st attribute buffer : vertices

        glUseProgram(programID);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(
            0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)0 // array buffer offset
        );
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    glfwTerminate();
    return 0;
}