public class Bicycle(){
    public int gears = 6;
    public int currentGear = 1;
    public int speed = 0;
    public int cadence = 0;
    public bool lights = false;
    public Wheel? Front_Wheel = new Wheel();
    public Wheel? Rear_Wheel = new Wheel();

    public void Pedal(int cadence){

    };
    public void ChangeGear(int currentGear){
    
    };
    public void Brakes(int brakes){

    };
};