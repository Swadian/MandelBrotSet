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
                m_vArray[j + i * pixelWidth].position = (m_pixel_size.j, m_pixel_size.i);
            }
        }
    }
}

void ComplexPlane::zoomIn() {
    m_zoomCount++;
	float xSize = BASE_WIDTH * (pow(BASE_ZOOM,m_zoomCount));
	float ySize = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM,m_zoomCount));
	m_plane_size(xSize,ySize);
	m_State = CALCULATING;

}

void ComplexPlane::zoomOut() {
    m_zoomCount--;
	float xSize = BASE_WIDTH * (pow(BASE_ZOOM,m_zoomCount));
	float ySize = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM,m_zoomCount));
	m_plane_size(xSize,ySize);
	m_State = CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel) {

}

void ComplexPlane::setMouseLocation(Vector2i mousPixel) {

}

void ComplexPlane::loadText(Text& text) {

}

size_t ComplexPlane::countIterations(Vector2f coord) {
    size_t count = 0;
    Vector2f z = coord;

    while(count < MAX_ITER) {
        float x = z.x * z.x - z.y * z.y + coord.x;
        float y = 2.0 * z.x * z.y + coord.y;

        z = Vector2f(x,y);

        if(z.x * z.x + z.y * z.y > 4.0) { break; }
        count++;
    }
    
    return count;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {
    if (count == MAX_ITER) {
        r = 0;
        g = 0;
        b = 0;
    }
    else if (count == 0 && count < 8) {
        r = 204;
        g = 0;
        b = 0;
    }
    else if (count >= 8 && count < 16) {
        r = 204;
        g = 102;
        b = 0;
    }
    else if (count >= 16 && count < 24) {
        r = 255;
        g = 255;
        b = 102;
    }
    else if (count >= 24 && count < 32) {
        r = 102;
        g = 178;
        b = 255;
    }
    else if (count >= 32 && count < 40) {
        r = 178;
        g = 102;
        b = 255;
    }
    else if (count >= 40 && count < 48){
        r = 255;
        b = 153;
        g = 255;
    }
    else if (count >= 48 && count < 56) {
        r = 255;
        b = 204;
        g = 229;
    }
    else {
        r = 255;
        g = 255;
        b = 255;
    }

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {
    Vector2f planeCord;
    planeCord.x = ((mousePixel.x - 0) / (m_plane_size.x - 0) ) * (m_plane_size.x) + (m_plane_center.x - m_plane_size.x / 2.0);
    planeCord.y = ((mousePixel.y - m_plane_size.y) / (0-m_plane_size.y)) * (m_plane_size.y) + (m_plane_center.y - m_palne_size.y / 2.0);
    return planeCord;
} 