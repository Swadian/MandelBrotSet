#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
    m_pixel_size = Vector2i(pixelWidth, pixelHeight);
    float m_aspectRatio = (pixelWidth*1.0)/(pixelHeight*1.0);
    m_plane_center = Vector2f(0,0);
    m_plane_size = Vector2f(BASE_WIDTH, BASE_HEIGHT*m_aspectRatio);
    int m_zoomCount = 0;
    m_state = State::CALCULATING;
    m_vArray = VertexArray(Points, pixelWidth*pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {
    target.draw(m_vArray);
}

void ComplexPlane::updateRender() {
    if(m_State == State.Calculating)
    {
        for(unsigned int j = 0; j < m_pixel_size.x; j++)//These paramenters don't 
                                                        //look right to me I think 
                                                        //its the m_pixel_size.x same 
                                                        //with the y
        {
            for(unsigned int i = 0; i < m_pixel_size.y; i++)
            {
                m_vArray.position = ;
            }
        }
    }
}

void ComplexPlane::zoomIn() {

}

void ComplexPlane::zoomOut() {

}

void ComplexPlane::setCenter(Vector2i mousePixel) {

}

void ComplexPlane::setMouseLocation(Vector2i mousPixel) {

}

void ComplexPlane::loadText(Text& text) {

}

size_t ComplexPlane::countIterations(Vector2f coord) {

}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {

}