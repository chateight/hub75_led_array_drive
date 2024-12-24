// to make clock pulse
void clock_func(byte port){
  //digitalWrite(0, HIGH);
  gpio_put(port, 1);  // in case of wite once, data wouldn't be captured correctly
  gpio_put(port, 1);
  gpio_put(port, 1);
  //digitalWrite(0, LOW);
  gpio_put(port, 0);
}

void refresh(){
  for (row_c = 0; row_c < 16; row_c++){
    // select row address
    gpio_put(oe, HIGH);
    gpio_put(a, a_sel[row_c]);
    gpio_put(b, b_sel[row_c]);
    gpio_put(c, c_sel[row_c]);
    gpio_put(d, d_sel[row_c]);
    gpio_put(e, e_sel[row_c]);    
// led display refreah cycle
//
// display row data with shade control
// due to the processing time, we prepare two similar code
// (if we set disp_data plate dimension as a variable, it will causes thirty percent processing time increasing)
  if (plane == 0){ 
    for (byte j = 0; j < 15; j++){
      row_set_0(j);
      gpio_put(oe, HIGH);
      clock_func(lat);
      gpio_put(oe, LOW);
    }
  } else {
    for (byte j = 0; j < 15; j++){
      row_set_1(j);
      gpio_put(oe, HIGH);
      clock_func(lat);
      gpio_put(oe, LOW);
    }
    }}}

// row data buffer write
void row_set_0(byte shade){
    for (byte i = 0; i < 64; i++){
      // color order b/g/r
      // red
      if (disp_data[0][2][row_c][i] > shade){
        gpio_put(r1, 1);        
      }
      else{
        gpio_put(r1, 0);
      }
      if (disp_data[0][2][row_c + 16][i] > shade){
        gpio_put(r2, 1);
      }
      else{
        gpio_put(r2, 0);
      }
      // green
      if (disp_data[0][1][row_c][i] > shade){
        gpio_put(g1, 1);
      }
      else{
        gpio_put(g1, 0);
      }
      if (disp_data[0][1][row_c + 16][i] > shade){
        gpio_put(g2, 1);
      }
      else{
        gpio_put(g2, 0);
      }
      //blue
      if (disp_data[0][0][row_c][i] > shade){
        gpio_put(b1, 1);
      }
      else{
        gpio_put(b1, 0);
      }
      if (disp_data[0][0][row_c + 16][i] > shade){
        gpio_put(b2, 1);
      }
      else{
        gpio_put(b2, 0);
      }
      // write to row buffer
      clock_func(clk);
    }
}

void row_set_1(byte shade){
    for (byte i = 0; i < 64; i++){
      // thanks color order b/g/r
      // red
      if (disp_data[1][2][row_c][i] > shade){
        gpio_put(r1, 1);        
      }
      else{
        gpio_put(r1, 0);
      }
      if (disp_data[1][2][row_c + 16][i] > shade){
        gpio_put(r2, 1);
      }
      else{
        gpio_put(r2, 0);
      }
      // green
      if (disp_data[1][1][row_c][i] > shade){
        gpio_put(g1, 1);
      }
      else{
        gpio_put(g1, 0);
      }
      if (disp_data[1][1][row_c + 16][i] > shade){
        gpio_put(g2, 1);
      }
      else{
        gpio_put(g2, 0);
      }
      //blue
      if (disp_data[1][0][row_c][i] > shade){
        gpio_put(b1, 1);
      }
      else{
        gpio_put(b1, 0);
      }
      if (disp_data[1][0][row_c + 16][i] > shade){
        gpio_put(b2, 1);
      }
      else{
        gpio_put(b2, 0);
      }
      // write to row buffer
      clock_func(clk);
    }
}