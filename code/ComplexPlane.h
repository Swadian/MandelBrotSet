#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <complex>
#include <cmath>

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum State {CALCULATING, DISPLAYING};
Class ComplexPlane() : public Drawable {
    public:
        ComplexPlane(int pixelWidth, int pixelHeight);
        void draw(RenderTarget& target, RenderStates states) const;
        void updateRender();
        void zoomIn();
        void zoomOut();
        void setCenter(Vector2i mousePixel);
        void setMouseLocation(Vector2i mousPixel);
        void loadText(Text& text);
    private:
        void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
        Vector2f mapPixelToCoords(Vector2i mousePixel);
        size_t countIterations(Vector2f coord);
        Vector2i m_pixel_size;
        float m_aspectRatio;
        Vector2f m_plane_center;
        Vector2f m_plane_size;
        size_t m_zoomCount;
        State m_state;
        VertexArray m_vArray;
        Vector2f m_mouseLocation;       
};