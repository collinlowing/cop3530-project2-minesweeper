#ifndef CEL_HPP
#define CEL_HPP

class Cell
{
    private:
    enum status {MINE, FLAG, NO_ADJACENT_MINES};
    public:
    Cell(bool mine);
    bool IsMine();
    void ToggleFlag();
    bool Click();
};

#endif