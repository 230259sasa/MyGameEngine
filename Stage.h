class FBX;
class Stage {
    FBX* pFbx[5];
    struct Data
    {
        int height;
        int type;
    };
    Data table[20][20];
public:
    //�R���X�g���N�^
    Stage();

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize();

    //�X�V
    void Update();

    //�`��
    void Draw();

    //�J��
    void Release();
};