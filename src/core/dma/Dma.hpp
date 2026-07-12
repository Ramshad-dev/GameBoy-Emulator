class DMA
{
public:
    void tick();

    bool active() const;

private:
    bool running = false;
};