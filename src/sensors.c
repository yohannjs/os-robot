


void sensorInit(){
  int initResult;
  initResult = ev3_sensor_init();
  if(initResult == 0){
   printf("No sensors connected\n");
 }else if(initResult == -1){
   printf("Error when initializing sensors\n");
 }else{
   printf("Initialized sensors. %d sensors connected\n", initResult );
 }
 if (ev3_search_sensor(LEGO_EV3_COLOR, &color_sn, 0)){
   set_sensor_mode(gyro_sn, "COLOR-COL");
   printf("Color sensor detected, set in ''COLOR-COL'' mode.\n");
 } else if(ev3_search_sensor(LEGO_EV3_US, &sonar_sn, 0)){
   //set_sensor_mode(gyro_sn, "GYRO-ANG");
   printf("Sonar detected.\n");
 }else {
   printf("No gyroscope found\n");
 }
}
