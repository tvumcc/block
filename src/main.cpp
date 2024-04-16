#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "physics_world.hpp"
#include "rectangle.hpp"

#define BG_COLOR sf::Color(40, 40, 40)
#define GUI_WIDTH 300

enum class Tool {
	Select,
	AddObject,
	StandardExplosion,
};

int main() {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1900u, 1000u), "Blocks", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(sf::Vector2i(0, 0));
	window.setFramerateLimit(144);

	bool success = ImGui::SFML::Init(window);

	sf::View view = sf::View(sf::FloatRect(0.0f, 0.0f, window.getSize().x, window.getSize().y));
	window.setView(view);

	PhysicsWorld ctx = PhysicsWorld(window.getSize().x - GUI_WIDTH, window.getSize().y, 100, 10000.0);

	sf::Clock clock;

	CollisionObject* currentObject = nullptr;
	bool pause = false;
	Tool tool = Tool::Select;

	float velocity_x = 0.0f;
	float velocity_y = 0.0f;
	float width = 100.0f;
	float height = 100.0f;
	float mass = 1.0f;
	float restitution = 0.75f;
	bool useGravity = true;

	ImVec4 color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
			ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x < window.getSize().x - GUI_WIDTH) {
				switch (tool) {
					case Tool::Select:
						currentObject = ctx.selectObject(event.mouseButton.x, event.mouseButton.y);
						break;
					case Tool::StandardExplosion: {
						CollisionObject* objectToExplode = ctx.selectObject(event.mouseButton.x, event.mouseButton.y);
						if (objectToExplode == currentObject) currentObject = nullptr;
						if (objectToExplode != nullptr) ctx.explodeRect(objectToExplode, 10, 10);
					} break;
					case Tool::AddObject: {
						Rectangle* newObj = new Rectangle(event.mouseButton.x, event.mouseButton.y, mass, width, height);
						newObj->velocity = Vec2(velocity_x, velocity_y);
						newObj->restitution = restitution;
						newObj->useGravity = useGravity;
						newObj->color = sf::Color(255.0f * color.x, 255.0f * color.y, 255.0f * color.z);
						ctx.addObject(newObj);
					} break;
				}
				
			}
        }

		sf::Time dt = clock.restart();
		window.clear(BG_COLOR);
		ImGui::SFML::Update(window, dt);

		if (!pause) ctx.update(dt.asMilliseconds());
		ctx.drawObjects(window);

		// Gui Stuff
		ImGui::SetNextWindowPos(ImVec2(window.getSize().x - GUI_WIDTH, 0));
		ImGui::SetNextWindowSize(ImVec2(GUI_WIDTH, window.getSize().y+2));
		ImGui::Begin("Blocks", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

		if  (ImGui::CollapsingHeader("Physics", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::Text("Object Count: %d", (int)ctx.objs.size()-4);
			ImGui::SliderInt("Step Rate", &ctx.stepsPerFrame, 1, 100);

			float gravityFloat = static_cast<float>(ctx.gravity);
			ImGui::SliderFloat("Gravity", &gravityFloat, 0.1f, 20.0f);
			ctx.gravity = static_cast<double>(gravityFloat);
			if (ImGui::Button("Pause")) pause = !pause;
			if (ImGui::Button("Clear All")) {
				for (int i = ctx.objs.size()-1; i >= 0; i--) {
					if (!ctx.objs[i]->isStatic) {
						ctx.objs.erase(ctx.objs.begin()+i);
					}
				}
			}
		}


		if  (ImGui::CollapsingHeader("Tools", ImGuiTreeNodeFlags_DefaultOpen))  {
			ImGui::Text("Current Tool: %d", (int)tool);
			if (ImGui::Button("Select Object")) tool = Tool::Select;
			if (ImGui::Button("Add Object")) tool = Tool::AddObject;
			if (ImGui::Button("Standard Explosion")) tool = Tool::StandardExplosion;
		}

		if (ImGui::CollapsingHeader("Add Object")) {
			ImGui::ColorEdit3("Color", (float*)&color);
			ImGui::Text("Velocity");
			ImGui::SliderFloat("X vel", &velocity_x, -100.0f, 100.0f);
			ImGui::SliderFloat("Y vel", &velocity_y, -100.0f, 100.0f);

			ImGui::Text(" ");
			ImGui::SliderFloat("Width", &width, 1.0f, 500.0f);
			ImGui::SliderFloat("Height", &height, 1.0f, 500.0f);
			ImGui::SliderFloat("Mass", &mass, 0.01f, 1000.0f);
			ImGui::SliderFloat("Restitution", &restitution, 0.01f, 0.99f);
			ImGui::Checkbox("Use Gravity", &useGravity);
		}

		if (ImGui::CollapsingHeader("Object Properties", ImGuiTreeNodeFlags_DefaultOpen)) {
			if (currentObject == nullptr) {
				ImGui::Text("No Object Selected");
			} else {
				ImGui::Text("Selected Object");

				ImGui::Text("Mass: %.3f", currentObject->mass);
				ImGui::Text("Affected by Gravity: %s", (currentObject->useGravity ? "true" : "false"));
				ImGui::Text("Position:     %.3f, %.3f", currentObject->position.x, currentObject->position.y);
				ImGui::Text("Velocity:     %.3f, %.3f", currentObject->velocity.x, currentObject->velocity.y);
				ImGui::Text("Acceleration: %.3f, %.3f", currentObject->acceleration.x, currentObject->acceleration.y);
				ImGui::Text("Force:        %.3f, %.3f", currentObject->force.x, currentObject->force.y);
				ImGui::Text("Impulse:      %.3f, %.3f", currentObject->impulse.x, currentObject->impulse.y);
			}
		}

		ImGui::End();
		ImGui::EndFrame();

		ImGui::SFML::Render(window);
        window.display();
    }

	ImGui::SFML::Shutdown();
}
