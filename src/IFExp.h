class IFExp
{
public:
    int startex, endex;
    IFExp(int START, int ENDEX);
    ~IFExp();
};

IFExp::IFExp(int START, int ENDEX){
    startex = START;
    endex = ENDEX;
}

IFExp::~IFExp(){
    startex = 0;
    endex = 1;
}