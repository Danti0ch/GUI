#include "Texture"

void draw_filled(GraphicSpace* space, uint x_l, uint y_l, uint x_u, uint y_u);
void draw_scretched(GraphicSpace* space, uint x_l, uint y_l, uint x_u, uint y_u);

void Texture::draw(GraphicSpace* space, uint x_l, uint y_l, uint x_u, uint y_u, TEXTURE_INSERT_MODE mode = TEXTURE_INSERT_MODE::SCRETCHING){

    if(x_l == x_u || y_l == y_u) return;

    Rectange rect = Rectange(x_l, y_l, x_u, y_u);

    if(is_solid_){
        rect.Draw(solid_col_);
        return;
    }
    
         if(mode == TEXTURE_INSERT_MODE::FILLING)    draw_scretched(space, x_l, y_l, x_u, y_u);
    else if(mode == TEXTURE_INSERT_MODE::SCRETCHING) draw_filled(space, x_l, y_l, x_u, y_u);

    return;
}
//----------------------------------------------------------------------------------------//

void Texture::draw(GraphicSpace* space, uint x_l, uint y_l, uint x_u, uint y_u, const std::set& mask, TEXTURE_INSERT_MODE mode = TEXTURE_INSERT_MODE::SCRETCHING){

}

//========================================================================================//

//                          LOCAL_FUNCTIONS_DEFINITION

//========================================================================================//

void draw_filled(GraphicSpace* space, uint x_l, uint y_l, uint x_u, uint y_u, bool mask_req, const std::set& mask){

    assert(space != NULL);

    uint x_tr_pxs = col_pixels_.n_cols();
    uint y_tr_pxs = col_pixels_.n_rows();

    uint ny_area_pxs = y_u - y_l + 1;
    uint nx_area_pxs = x_u - x_l + 1;
    
    uint n_rows = ny_area_pxs / y_tr_pxs;
    uint n_cols = nx_area_pxs / x_tr_pxs;

    bool x_trim_req = (n_cols * x_tr_pxs != nx_area_pxs);
    bool y_trim_req = (n_rows * y_tr_pxs != ny_area_pxs);
    
    std::vector<Pixel> pixs();

    for(uint y_ind = 0; y_ind < n_y_area_pxs; y_ind++){
        for(uint x_ind = 0; x_ind < n_x_area_pxs; x_ind++){
            
        }
    }
    for(uint n_row = 0; n_row < n_rows; n_row++){
        for(uint n_col = 0; n_col < n_cols; n_col++){
            
            for(uint y_ind = y_l + n_row * y_tr_pxs; y_ind < y_l + (n_row + 1) * y_tr_pxs; y_ind++){
                for(uint x_ind = x_l + n_col * x_tr_pxs; x_ind < x_l + (n_col + 1) * y_tr_pxs; x_ind++){

                }
            }

            if(!mask_req || mask.contains({n_row, n_col})){
                space->DrawPixels(col_pixels_.data, x_l + n_col       * x_tr_pxs, 
                                                    y_l + n_row       * y_tr_pxs, 
                                                    x_l + (n_col + 1) * y_tr_pxs - 1, 
                                                    y_l + (n_row + 1) * y_tr_pxs - 1);
            }
        }
    }

    if(x_trim_req){
        Matrix<Color> trim_col_pixs = col_pixels_.submatrix(0, y_tr_pxs - 1, 0, nx_area_pxs - x_tr_pxs * n_cols);
        
        for(uint n_row = 0; n_row < n_rows; n_row++){
            if(!mask_req || mask.contains({n_row, n_col})){
                space->DrawPixels(trim_col_pixs.data,   x_l + n_cols       * x_tr_pxs, 
                                                        y_l + n_row        * y_tr_pxs, 
                                                        x_u, 
                                                        y_l + (n_row  + 1) * y_tr_pxs - 1);
            }
        }
    }

    if(y_trim_req){
        Matrix<Color> trim_col_pixs = col_pixels_.submatrix(0, ny_area_pxs - y_tr_pxs * n_rows, 0, x_tr_pxs - 1);

        for(uint n_col = 0; n_col < n_cols; n_col++){
            if(!mask_req || mask.contains({n_row, n_col})){
                space->DrawPixels(trim_col_pixs.data,   x_l + n_col       * x_tr_pxs, 
                                                        y_l + n_rows      * y_tr_pxs, 
                                                        x_l + (n_col + 1) * y_tr_pxs - 1, 
                                                        y_u);
            } 
        }
    }

    if(x_trim_req && y_trim_req){
        Matrix<Color> trim_col_pixs = col_pixels_.submatrix(0, ny_area_pxs - y_tr_pxs * n_rows, 0, nx_area_pxs - x_tr_pxs * n_cols);

        if(!mask_req || mask.contains({n_row, n_col})){
            space->DrawPixels(trim_col_pixs.data,   x_l + n_cols       * x_tr_pxs, 
                                                    y_l + n_rows       * y_tr_pxs, 
                                                    x_u, 
                                                    y_u);
        }
    }
    return;
}
//----------------------------------------------------------------------------------------//

void draw_scretched(GraphicSpace* space, uint x_l, uint y_l, uint x_u, uint y_u){

    assert(space != NULL);

    uint x_tr_pxs = col_pixels_.n_cols();
    uint y_tr_pxs = col_pixels_.n_rows();

    uint ny_area_pxs = y_u - y_l + 1;
    uint nx_area_pxs = x_u - x_l + 1;
    
    if(x_tr_pxs == nx_area_pxs && y_tr_pxs == ny_area_pxs){
        space->DrawPixels(col_pixels_, x_l, y_l, x_u, y_u);
        return;
    }
    
    Matrix<Color> pixs_to_draw(ny_area_pxs, nx_area_pxs);

    double x_scr_ratio = (double)x_tr_pxs / (double)nx_area_pxs;
    double y_scr_ratio = (double)y_tr_pxs / (double)ny_area_pxs;
    
    for(uint n_row = 0; n_row < ny_area_pxs; n_row++){
        for(uint n_col = 0; n_col < nx_area_pxs; n_col++){
            pixs_to_draw.set(n_row, n_col, col_pixels_.get((uint)(n_row * y_scr_ratio), (uint)(n_col * x_scr_ratio)));
        }
    }

    space->DrawPixels(pixs_to_draw.data, x_l, y_l, x_u, y_u);
    return;
}
//----------------------------------------------------------------------------------------//
