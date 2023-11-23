#include "ComplexPlane.h"

int main() {
    int width = VideoMode::getDesktopMode().width/2;
    int height = VideoMode::getDesktopMode().height / 2;
    VideoMode vm(width, height);
    RenderWindow window(vm,"Mandelbrot Set",Style::Default);

    ComplexPlane plane(width, height);

    Font font;
    if (!font.loadFromFile("Roboto-Light.ttf")) {
        cout << "Error loading font" << endl;
    }

    Text text("",font,24);

    while(window.isOpen()) {

        sf::Event event;
        
        while (window.pollEvent(event)) {
            
            if (event.type == Event::Closed) { window.close(); }
            
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    plane.zoomOut();
                    Vector2i position(event.mouseButton.x, event.mouseButton.y);
                    plane.setCenter(position);
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    plane.zoomIn();
                    Vector2i position(event.mouseButton.x, event.mouseButton.y);
                    plane.setCenter(position);
                }
            }
            if (event.type == Event::MouseMoved) {
                Vector2i position(event.mouseMove.x, event.mouseMove.y);
                plane.setMouseLocation(position);
            }
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); }

        plane.updateRender();
        plane.loadText(text);
        window.clear();
        window.draw(plane);
        window.draw(text);
        window.display();
    }
}

