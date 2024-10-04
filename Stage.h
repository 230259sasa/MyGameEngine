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
    //コンストラクタ
    Stage();

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize();

    //更新
    void Update();

    //描画
    void Draw();

    //開放
    void Release();
};