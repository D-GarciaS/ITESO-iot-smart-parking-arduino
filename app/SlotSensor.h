class SlotSensor
{
  public:
    int number;
    bool preferential;
    bool occupied;
    int pin;
    unsigned long lastRead;

    SlotSensor() {}
    SlotSensor(int number, int sensorPin);

    void readSensor();
    bool hasChanged();
    void confirmChange();

  private:
    bool changed;
};