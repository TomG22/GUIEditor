#include "Gui.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

Gui::Gui()
    : window(nullptr) {

}

void Gui::RegisterListener(GuiListener* listener) {
    listeners.push_back(listener);
}

bool Gui::isKeyDown(int keyCode) {
    if (!window) return false;

	return glfwGetKey(window, keyCode) != 0;
}

void glfwErrorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

int Gui::startGuiLoop() {
// WINDOW CODE //
    // Set the debug callback for all GLFW errors
    glfwSetErrorCallback(glfwErrorCallback);

    // Check if GLFW initialization errors
    if (!glfwInit()) {
        fprintf(stderr, "Gui ERROR: GLFW initialization failed\n");
        return 1;
    }

    // Create the GLFW window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1920, 1080, "GLFW Window", glfwGetPrimaryMonitor(), nullptr);

    // Check if window creation errors
    if (window == nullptr) {
        fprintf(stderr, "Gui ERROR: GLFW window initialization failed\n");
        glfwTerminate();
        return 1;
    }

    // Set the current context to our window
    glfwMakeContextCurrent(window);

    // Set the window attributes
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Save the reference of the current gui instance
    glfwSetWindowUserPointer(window, this);

    // Set the callbacks for the window
    glfwSetKeyCallback(window, Gui::keyCallback);
    glfwSetErrorCallback(glfwErrorCallback);

    // Check if GLAD initialization errors
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "Gui ERROR: GLAD initialization failed\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }
// END OF WINDOW CODE //


    //float positions[] = {
    //    -0.5f, -0.5f, 0.0f, 0.0f,
    //     0.5f, -0.5f, 1.0f, 0.0f,
    //     0.5f,  0.5f, 1.0f, 1.0f,
    //    -0.5f,  0.5f, 0.0f, 1.0f
    //};

    float positions[] = {
        -1.0f, -1.0f,   1.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f,   0.0f, 1.0f, 0.0f, 0.0f,
         1.0f,  1.0f,   0.0f, 0.0f, 1.0f, 0.0f,
        -1.0f,  1.0f,   1.0f, 1.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;
    VertexBuffer vb(positions, 4 * 6 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(4);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
/*
    //Shader shader2D("res/shaders/BaseColor.shader");
    //shader2D.Bind();
    //shader2D.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    Shader shader2D("./res/shaders/2DVertexColor.shader");
    //Texture texture = Texture("res/imgs/popcat.png", "diffuse", 0);
    shader2D.Bind();
    //shader2D.SetUniform1i("u_Texture", 0);

    //shader2D.SetUniform4f("u_Color", 0.0f, 1.0f, 0.8f, 1.0f);

    //float aspectRatio = 1920.0f/1080.0f;
    //glm::mat4 aspectProj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
    //shader2D.SetUniformMat4f("u_Proj", aspectProj);

    //Shader shader3D("res/shaders/3D.shader");
    //glm::vec3 lightPos = glm::vec3(.5f, .5f, .5f);
    //glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    //glm::mat4 lightModel = glm::mat4(1.0f);
    //lightModel = glm::translate(lightModel, lightPos);

    //shader3D.Bind();
    //shader3D.SetUniform3f("u_LightPos", lightPos.x, lightPos.y, lightPos.z);
    //shader3D.SetUniform4f("u_LightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader2D.Unbind();
    //shader3D.Unbind();

*/
    Renderer renderer;
    std::vector<Texture> textures;

    //Mesh meshTest = Mesh(va, ib, textures);
    //Camera camera(1920, 1080, glm::vec3(0.0f, 0.0f, 2.0f));

    //renderer.clearColor(0.9f, 0.9f, 0.9f, 1.0f);
    renderer.clearColor(0.3f, 0.9f, 0.9f, 1.0f);
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //camera.Inputs(window);
        //camera.updateMatrix(45.0f, 0.01f, 80.0f);
        renderer.Clear();



        //texture.Bind();
        //renderer.Draw(va, ib, shader2D);

        /*meshTest.Draw(shader3D,
                  camera,
                  glm::mat4(1.0f),
                  glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                  glm::vec3(1.0f, 1.0f, 1.0f));
        */

        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void Gui::handleKey(int key, int scancode, int action, int mods) {
    for (auto* listener : listeners) {
        listener->OnKey(key, scancode, action, mods);
    }
}

void Gui::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Get a reference to the gui for our key callback
    Gui* gui = static_cast<Gui*>(glfwGetWindowUserPointer(window));
    if (gui) {
        // Call the non-static keyCallback member function
        gui->handleKey(key, scancode, action, mods);
    }
}

void Gui::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
