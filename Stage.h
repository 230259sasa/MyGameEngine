#include <Windows.h>

class FBX;
class Stage {
    FBX* pFbx[5];
    struct Data
    {
        int height;
        int type;
    };
    Data table[20][20];

    enum SELECT_MODE {
        Up = 0,
        Down,
        Change
    };

    int selectMode;
    int selectType;

    void Save();

    void Open();
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

    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
};