#include "drawable_objects.h"
#include "tests.h"
#include "Vector3D.h"
#include <math.h>
#include <assert.h>
#include <iostream>

static const double EPS = 1e-8;

static const uint WINDOW_HEIGHT = 720;
static const uint WINDOW_WIDTH  = 1080;

static const double CTS1_CT_X_INIT = 10;
static const double CTS1_CT_Y_INIT = 10;

static const double TIME_VECTOR_LEN = 8;

//========================================================================================//

//                          PUBLIC_FUNCTIONS_DEFINITION

//========================================================================================//

ActionVectorsRender::ActionVectorsRender():
    space_(WINDOW_WIDTH, WINDOW_HEIGHT),
    butt_reset_(40, 490, 140, 540, Color(252, 29, 170)),
    butt_speed_(160, 490, 260, 540, Color(254, 6, 43)),
    butt_exit_(280, 490, 380, 540, Color(78, 101, 202)),
    cts1_(10, 210, 10, 210, -10, 10, -10, 10),
    time_cts_group_({
        CoordinateSus(460, 560, 300, 400, -10, 10, -10, 10),
        CoordinateSus(580, 680, 300, 400, -10, 10, -10, 10),
        CoordinateSus(700, 800, 300, 400, -10, 10, -10, 10)
    })
{

    space_.SetMouseButtonPressEvent(mouse_press_event);
    space_.SetUpdateHandler(update_handler);

    // TODO: add text button

    cts1_ct_x_ = CTS1_CT_X_INIT;
    cts1_ct_y_ = CTS1_CT_Y_INIT;

    time_arrow_speed_ratio_ = 1;
    cur_sec_val_            = 0;
    init_time_ = clock();
}
//----------------------------------------------------------------------------------------//

void ActionVectorsRender::Init(){

    space_.HandleEvents();

    return;
}
//----------------------------------------------------------------------------------------//

//========================================================================================//

//                          LOCAL_FUNCTIONS_DEFINITION

//========================================================================================//

void ActionVectorsRender::mouse_press_event(GraphicSpace* space, int x_pos, int y_pos){

    assert(space != NULL);

    if(CheckCoordInCTS(cts1_, x_pos, y_pos)){
        cts1_ct_x_ = cts1_.CountAxisPosX(x_pos);
        cts1_ct_y_ = cts1_.CountAxisPosY(y_pos);
    }

    if(CheckCoordInButton(butt_reset_, x_pos, y_pos)){
        cts1_ct_x_ = CTS1_CT_X_INIT;
        cts1_ct_y_ = CTS1_CT_Y_INIT;

        time_arrow_speed_ratio_ = 1;
    }

    if(CheckCoordInButton(butt_speed_, x_pos, y_pos)){
        time_arrow_speed_ratio_ << 1;
    }

    if(CheckCoordInButton(butt_exit_, x_pos, y_pos)){
        space->Close();
    }

    return;
}
//----------------------------------------------------------------------------------------//

// TODO: space remove ?? 
void ActionVectorsRender::update_handler(GraphicSpace* space){

    assert(space != NULL);

    space->Clear();
    // TODO:
    space->Draw(butt_reset_);
    space->Draw(butt_speed_);
    space->Draw(butt_exit_);

    cts1_.Draw(space);
    time_cts_group_[0].Draw(space);
    time_cts_group_[1].Draw(space);

    if(time_arrow_speed_ratio_ * (clock() - init_time_) >= CLOCKS_PER_SEC){
        cur_sec_val_ = (cur_sec_val_ + (int)floor(time_arrow_speed_ratio_ * (clock() - init_time_) / CLOCKS_PER_SEC)) % 60; 
        init_time_   = clock();
    }

    double time_vtor_angle = M_PI / 2 - (2 * M_PI) / 60 * cur_sec_val_;

    Vector code_time_vtor(TIME_VECTOR_LEN, time_vtor_angle, VT_DATA::POLAR);

    code_time_vtor.Draw(space, time_cts_group_[0]);
    code_time_vtor.Draw(space, time_cts_group_[1]);
    code_time_vtor.Draw(space, time_cts_group_[2]);

    Vector click_vtor(cts1_ct_x_, cts1_ct_y_, VT_DATA::COORD);
    click_vtor.Draw(space, cts1_);

    space->Show();

    return;
}
//----------------------------------------------------------------------------------------//
