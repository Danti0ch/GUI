#ifndef GRAPHICAL_PRIMS
#define GRAPHICAL_PRIMS

class Vector : public geom::Vector{
public:

    Vector();
    Vector(const geom::Vector& vt);
    Vector(double v1, double v2, VT_DATA mod);
    Vector(double v1, double v2, VT_DATA mod, Color col);
    
    void Draw(GraphicSpace* editor, const CoordinateSus& ct_sus, Color col = Color(255, 0, 0));
    void Draw(GraphicSpace* editor, const CoordinateSus& ct_sus, double x_init, double y_init, Color col = Color(255, 0, 0));
    void Draw(GraphicSpace* editor, const CoordinateSus& ct_sus, const Vector& vt_init, Color col = Color(255, 0, 0));
private:
    Color col_;
};
//----------------------------------------------------------------------------------------//

#endif // GRAPHICAL_PRIMS
