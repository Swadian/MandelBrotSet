#include "ComplexPlane.cpp"

using namespace sf;
using namespace std;

int main() {
    VideoMode vm(VideoMode::getDesktopMode().width/2,VideoMode::getDesktopMode().height / 2);
    RenderWidnow window(vm,"Mandelbrot Set",Style::Default);

    ComplexPlane plane(vm.height(),vm.width());

    Font font;
    if (!font.loadFromFile("Roboto-Light.ttf")) {
        cout << "Error loading font" << endl;
    }

    Text text("",font,24);

    while(window.isOpen()) {

        sf::Event event;
        
        while (window.pollEvent(event)) {
            
            if (event.type == Event::closed) { window.close(); }
            
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    zoomOut();
                    plane.setCenter(mouseButton);
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    zoomIn();
                    plane.setCenter(mouseButton);
                }
            }
            if (event.type == Event::MouseMoved) {
                plane.setMouseLocation(mouseButton);
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

