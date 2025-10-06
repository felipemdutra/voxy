#include <memory>
#include <wrapgl/wrapgl.h>

#include <GLFW/glfw3.h>

using namespace wgl;
using namespace std;

constexpr int kWindowWidth  = 800;
constexpr int kWindowHeight = 600;

VertexLayout layout;

VertexLayout& GetGlobalDefaultVertexLayout() {
        return layout;
}

int main()
{
        layout.AddAttr(0, kPosition, 3, GL_FLOAT, false);
        layout.AddAttr(1, kColor, 3, GL_FLOAT, true);

        auto window = Window(kWindowWidth, kWindowHeight, "Voxy Engine");

        auto renderer = Renderer();

        const auto default_program = make_shared<ShaderProgram>(
                "shaders/default_vert.glsl", "shaders/default_frag.glsl");

        renderer.BindProgram("default", default_program.get());
        renderer.UseProgram("default");

        PerspectiveCamera camera = PerspectiveCamera(
                default_program.get(),
                "view",
                "proj",
                45.0f,
                (float)kWindowWidth/kWindowHeight,
                0.5f,
                1000.0f
                );

        while (!window.ShouldClose()) {
                renderer.Clear(0.2f, 0.4f, 1.0f, 1.0f, true);
                
                window.SwapBuffers();
                glfwPollEvents();
        }
}

