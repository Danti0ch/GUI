#include "graphical_primitives.h"
#include <assert.h>

static const uint ARROW_LINE_LEN = 10;

static const Color VECTOR_COLOR = Color(200, 0, 0, 200);

static void draw_real_line(GraphicSpace* editor, const CoordinateSus& ct_sus, double x_from, double y_from, double x_to, double y_to, Color col){

    assert(editor != NULL);

    int pix_from_x_ct = ct_sus.CountPixelPosX(x_from);
    int pix_from_y_ct = ct_sus.CountPixelPosY(y_from);
    int pix_to_x_ct   = ct_sus.CountPixelPosX(x_to);
    int pix_to_y_ct   = ct_sus.CountPixelPosY(y_to);

    if(pix_from_x_ct < ct_sus.x_lower_pixel() || pix_from_x_ct > ct_sus.x_upper_pixel()) return;
    if(pix_from_y_ct < ct_sus.y_upper_pixel() || pix_from_y_ct > ct_sus.y_lower_pixel()) return;
    if(pix_to_x_ct   < ct_sus.x_lower_pixel() || pix_to_x_ct   > ct_sus.x_upper_pixel()) return;
    if(pix_to_y_ct   < ct_sus.y_upper_pixel() || pix_to_y_ct   > ct_sus.y_lower_pixel()) return;

    editor->DrawLine(pix_from_x_ct, pix_from_y_ct, pix_to_x_ct, pix_to_y_ct, col);

    return;
}
//----------------------------------------------------------------------------------------//

void DrawVtor(GraphicSpace* editor, const Vector& vt_to_draw, const CoordinateSus& ct_sus, double x_init, double y_init, Color col){
    
    assert(editor != NULL);

    double x_final_ct = x_init + vt_to_draw.x();
    double y_final_ct = y_init + vt_to_draw.y();
    
    draw_real_line(editor, ct_sus, x_init, y_init, x_final_ct, y_final_ct, col);
    
    Vector vt_normal = vt_to_draw.NormalVector(vt_to_draw.len());

    // HERE MAN
    //arrow_line = arrow_line - (*this / (double)LEN_ARROW_LINE_RATIO);
    Vector arrow_line = vt_normal - vt_to_draw;
    arrow_line.ChangeLen(ARROW_LINE_LEN);
    arrow_line.x(arrow_line.x() / ct_sus.scale_x());
    arrow_line.y(arrow_line.y() / ct_sus.scale_y());
    
    draw_real_line(editor, ct_sus, x_final_ct, y_final_ct, x_final_ct + arrow_line.x(), y_final_ct + arrow_line.y(), col);

    arrow_line = -vt_normal - vt_to_draw;
    arrow_line.ChangeLen(ARROW_LINE_LEN);
    arrow_line.x(arrow_line.x() / ct_sus.scale_x());
    arrow_line.y(arrow_line.y() / ct_sus.scale_y());
    
    draw_real_line(editor, ct_sus, x_final_ct, y_final_ct, x_final_ct + arrow_line.x(), y_final_ct + arrow_line.y(), col);

    return;
}
//----------------------------------------------------------------------------------------//

void DrawVtor(GraphicSpace* editor, const Vector& vt_to_draw, const CoordinateSus& ct_sus, Color col){

    assert(editor != NULL);

    DrawVtor(editor, vt_to_draw, ct_sus, 0, 0, col);
    return;
}
//----------------------------------------------------------------------------------------//

void DrawVtor(GraphicSpace* editor, const Vector& vt_to_draw, const CoordinateSus& ct_sus, const Vector& vt_init, Color col){

    assert(editor  != NULL);

    DrawVtor(editor, vt_to_draw, ct_sus, vt_init.x(), vt_init.y(), col);
    return;
}
//----------------------------------------------------------------------------------------//
