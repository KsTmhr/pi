#include <limits.h>

#define KETA 1010

struct NUMBER
{
    int n[KETA]; // 各桁の値
    int sign;    // 符号変数
};

typedef struct NUMBER number;

// プロトタイプ宣言
void clearByZero(number *);
void dispNumber(const number *);
void dispNumberZeroSuppress(const number *);
void dispNumberLN(const number *);
void dispNumberZSLN(const number *);
void setRnd(number *, int);
void copyNumber(const number *, number *);
void getAbs(const number *, number *);
int isZero(const number *);
int mulBy10(const number *, number *);
int divBy10(number *, number *);
int setInt(number *, int);
int setIntFromString(number *, char *);
int getInt(const number *, int *);
int getIntAsString(number *, char *, int);
int setSign(number *, int);
int getSign(const number *);
int numComp(const number *, const number *);
void swap(number *, number *);
int preAdd(const number *, const number *, number *);
int add(const number *, const number *, number *);
int prepreSub(const number *, const number *, number *);
int preSub(const number *, const number *, number *);
int sub(const number *, const number *, number *);
int getDigit(const number *);
int getDigitOfInt(const int);
int increment(number *, number *);
int decrement(number *, number *);
int simpleMultiple(int, int, int *);
int multiple(const number *, const number *, number *);
int simpleDivide(int, int, int *, int *);
int divide(const number *, const number *, number *, number *);
int divide2(const number *, const number *, number *, number *);
int factorial(const number *, number *);
int squareroot(const number *, number *);
int mySin(const number *, number *);
int myCos(const number *, number *);

//
// 多倍長変数の値をゼロクリアし，符号をプラスにセットする
//
void clearByZero(number *a)
{
    int i;

    for (i = 0; i < KETA; i++)
    {
        a->n[i] = 0;
    }

    setSign(a, 1);
}

//
// aを表示する
//
void dispNumber(const number *a)
{
    int i;

    if (getSign(a) >= 0)
    {
        printf("+");
    }
    else
    {
        printf("-");
    }

    for (i = KETA - 1; i >= 0; i--)
    {
        printf("%2d", a->n[i]);
        if (i % 10 == 0)
        {
            printf("\n");
        }
        if (i % 100 == 0)
        {
            printf("\n");
        }
    }
}

//
// 桁数を返す
//
int getDigit(const number *a)
{
    int num = KETA - 1;
    while (a->n[num] == 0 && num > 0)
    {
        num--;
    }
    return num + 1;
}

//
// int型変数の桁数を返す
//
int getDigitOfInt(const int x)
{
    int d, keta;
    d = x;
    keta = 0;
    while (d != 0)
    {
        d /= 10;
        keta++;
    }
    return keta;
}

//
// aをゼロサプレス表示
//
void dispNumberZeroSuppress(const number *a)
{
    int i;

    if (getSign(a) == -1)
    {
        putchar('-');
    }
    else
    {
        putchar('+');
    }

    for (i = getDigit(a) - 1; i >= 0; i--)
    {
        printf("%d", a->n[i]);
    }
}

//
// 改行付きのdispNumber()
//
void dispNumberLN(const number *a)
{
    dispNumber(a);
    putchar('\n');
}

//
// 改行付きdispNumberZeroSuppress()
//
void dispNumberZSLN(const number *a)
{
    dispNumberZeroSuppress(a);
    putchar('\n');
}

//
// 乱数をセット
//
void setRnd(number *a, int k)
{
    int i, keta;
    int zeroFlag = 1;

    if (k > KETA)
    {
        keta = KETA;
    }
    else if (k < 0)
    {
        keta = 0;
    }
    else
    {
        keta = k;
    }

    clearByZero(a);
    for (i = keta - 1; i >= 0; i--)
    {
        a->n[i] = rand() % 10;
        if (a->n[i] != 0)
        {
            zeroFlag = 0;
        }
    }

    if ((rand() % 10) > 5 || zeroFlag)
    {
        setSign(a, 1);
    }
    else
    {
        setSign(a, -1);
    }
}

//
// aをbにコピーする
//
void copyNumber(const number *a, number *b)
{
    int i;
    for (i = 0; i < KETA; i++)
    {
        b->n[i] = a->n[i];
    }
    setSign(b, getSign(a));
}

//
// aの絶対値をbに返す
//
void getAbs(const number *a, number *b)
{
    copyNumber(a, b);
    setSign(b, 1);
}

//
// aがゼロか判別する
//
// 戻り値
//      0 ... a == 0
//     -1 ... a != 0
//
int isZero(const number *a)
{
    int i;
    if (getSign(a) < 0)
    {
        return -1;
    }

    for (i = KETA - 1; i >= 0; i--)
    {
        if (a->n[i] != 0)
        {
            return -1;
        }
    }
    return 0;
}

//
// aを10倍してbに返す
//
// 戻り値
//      0 ... 正常終了
//     -1 ... オーバーフロー
int mulBy10(const number *a, number *b)
{
    int i, r;
    if (a->n[KETA - 1] != 0)
    {
        r = -1;
    }
    else
    {
        r = 0;
    }
    for (i = KETA - 1; i > 0; i--)
    {
        b->n[i] = a->n[i - 1];
    }
    b->n[0] = 0;
    setSign(b, getSign(a));

    return r;
}

//
// aを1/10倍してbに返す
//
// 戻り値
//      aを10で割った余り
//
int divBy10(number *a, number *b)
{
    int i, r;
    int zeroflag = 1;

    if (getSign(a) < 0)
    {
        r = a->n[0] * -1;
    }
    else
    {
        r = a->n[0];
    }

    for (i = 0; i < KETA - 1; i++)
    {
        b->n[i] = a->n[i + 1];
        if (b->n[i] != 0)
        {
            zeroflag = 0;
        }
    }
    b->n[KETA - 1] = 0;

    if (zeroflag)
    {
        setSign(b, 1);
    }
    else
    {
        setSign(b, getSign(a));
    }

    return r;
}

//
// 多倍長変数aにint型変数xの値を設定する
//
// 戻り値
//      0 ... 正常終了
//     -1 ... xの値がaに設定しきれなかった．
//
int setInt(number *a, int x)
{
    int i, r, re;
    int x2 = x;
    int keta = getDigitOfInt(x);

    re = 0;

    clearByZero(a);

    if (x >= 0)
    {
        setSign(a, 1);
    }
    else
    {
        x2 *= -1;
        setSign(a, -1);
    }

    for (i = 0; i < keta; i++)
    {
        if (i == KETA)
        {
            re = -1;
            break;
        }

        r = x2 % 10;
        x2 /= 10;
        a->n[i] = r;
    }

    return re;
}

//
// 多倍長変数aにint型変数xの値を設定する
//
// 戻り値
//      0 ... 正常終了
//     -1 ... strの値がaに設定しきれなかった．
//
int setIntFromString(number *a, char *str)
{
    int i, l, l2;
    char *str2 = str;

    clearByZero(a);

    // 長さ測定
    l = 0;
    while (str[l] != '\0')
    {
        l++;
    }
    l2 = l;

    // 符号決定
    if (str[0] == '-')
    {
        l2--;
        setSign(a, -1);
    }
    else
    {
        setSign(a, 1);
    }

    for (i = 0; i < l2; i++)
    {
        if (i == KETA)
        {
            clearByZero(a);
            return -1;
        }
        a->n[i] = str[l - 1 - i] - '0';
    }

    return 0;
}

//
// int型変数xに多倍長変数aの値を設定する
//
// 戻り値
//      0 ... 正常終了
//     -1 ... aの値がxに設定しきれなかった．
//
int getInt(const number *a, int *x)
{
    int i;
    int p, power, keta;

    keta = getDigitOfInt(INT_MAX);

    if (keta < getDigit(a))
    {
        *x = 0;
        return -1;
    }

    p = 0;
    power = 1;
    for (i = 0; i < KETA; i++)
    {
        p += a->n[i] * power;
        power *= 10;
    }

    if (getSign(a) == -1)
        p *= -1;

    *x = p;

    return 0;
}

//
// char *型変数strに多倍長変数aの値を設定する
//
// 戻り値
//      0 ... 正常終了
//     -1 ... aの値がstrに設定しきれなかった．
//
int getIntAsString(number *a, char *str, int l)
{
    int i, keta;
    if (getSign(a) == 1)
    {
        str[0] = '+';
    }
    else
    {
        str[0] = '-';
    }

    keta = getDigit(a);

    if (keta + 1 > l)
    {
        return -1;
    }

    for (i = keta - 1; i >= 0; i--)
    {
        str[keta - i] = '0' + a->n[i];
    }
    str[keta - i] = '\0';

    return 0;
}

//
// 多倍長変数aの符号を
// s=1なら正に，s=-1なら負に設定して0を返す
// それ以外はエラーとして-1を返す
//
int setSign(number *a, int s)
{
    switch (s)
    {
    case 1:
        a->sign = 1;
        return 0;
        break;

    case -1:
        a->sign = -1;
        return 0;
        break;

    default:
        return -1;
        break;
    }
}

//
// aが0か正なら+1を，負なら-1を返す
//
int getSign(const number *a)
{
    return a->sign;
}

//
// 2つの多倍長変数 a, b の大小を比較する
//
// 戻り値
//      0 ... a = b
//      1 ... a > b
//     -1 ... a < b
int numComp(const number *a, const number *b)
{
    int i;
    int Sa, Sb;

    Sa = getSign(a);
    Sb = getSign(b);

    // aが正 bが負
    if (Sa == 1 && Sb == -1)
    {
        return 1;
    }
    // aが正 bも正
    else if (Sa == 1 && Sb == 1)
    {
        for (i = KETA - 1; i >= 0; i--)
        {
            if (a->n[i] > b->n[i])
                return 1;
            else if (b->n[i] > a->n[i])
                return -1;
        }
        return 0;
    }
    // aが負 bが正
    else if (Sa == -1 && Sb == 1)
    {
        return -1;
    }
    // aが負 bも負
    else if (Sa == -1 && Sb == -1)
    {
        for (i = KETA - 1; i >= 0; i--)
        {
            if (a->n[i] > b->n[i])
                return -1;
            else if (b->n[i] > a->n[i])
                return 1;
        }
        return 0;
    }
    // unexpected
    else
    {
        return -100;
    }
}

//
// aとbを交換する
//
void swap(number *a, number *b)
{
    int i, tmp, signTmp;
    signTmp = getSign(a);
    setSign(a, getSign(b));
    setSign(b, signTmp);
    for (i = 0; i < KETA; i++)
    {
        tmp = a->n[i];
        a->n[i] = b->n[i];
        b->n[i] = tmp;
    }
}

//
// 脳死で足し算
//
int preAdd(const number *a, const number *b, number *c)
{
    int i, d;
    d = 0;
    for (i = 0; i < KETA; i++)
    {
        d = a->n[i] + b->n[i] + d;
        c->n[i] = d % 10;
        d /= 10;
    }
    setSign(c, 1);
    if (d == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

//
// c <- a + b
// 戻り値
//      0 ... 正常終了
//     -1 ... オーバーフロー
//
int add(const number *a, const number *b, number *c)
{
    int r, Sa, Sb;
    number tmp1, tmp2;

    Sa = getSign(a);
    Sb = getSign(b);

    // aが正 bも正
    if (Sa == 1 && Sb == 1)
    {
        r = preAdd(a, b, c);
    }
    // aが正 bは負
    else if (Sa == 1 && Sb == -1)
    {
        getAbs(b, &tmp1);
        r = preSub(a, &tmp1, c);
    }
    // aが負 bは正
    else if (Sa == -1 && Sb == 1)
    {
        getAbs(a, &tmp1);
        r = preSub(b, &tmp1, c);
    }
    // aが負 bも負
    else if (Sa == -1 && Sb == -1)
    {
        getAbs(a, &tmp1);
        getAbs(b, &tmp2);
        r = preAdd(&tmp1, &tmp2, c);
        setSign(c, -1);
    }
    // unexpected
    else
    {
        r = -1;
    }

    return r;
}

//
// 脳死で引き算
//
int prepreSub(const number *a, const number *b, number *c)
{
    int i;
    int h = 0;
    for (i = 0; i < KETA; i++)
    {
        if (a->n[i] - h >= b->n[i])
        {
            c->n[i] = a->n[i] - b->n[i] - h;
            h = 0;
        }
        else
        {
            c->n[i] = 10 + a->n[i] - b->n[i] - h;
            h = 1;
        }
    }
    if (h == 0)
        return 0;
    else
        return -1;
}

//
// 正 - 正のみ対応
//
int preSub(const number *a, const number *b, number *c)
{
    int r;
    switch (numComp(a, b))
    {
    case 1:
        r = prepreSub(a, b, c);
        setSign(c, 1);
        break;
    case -1:
        r = prepreSub(b, a, c);
        setSign(c, -1);
        break;
    case 0:
        clearByZero(c);
        r = 0;
        break;
    default:
        r = -1;
        break;
    }
    return r;
}

//
// c <- a - b
// 戻り値
//      0 ... 正常終了
//     -1 ... オーバーフロー
//
int sub(const number *a, const number *b, number *c)
{
    int r, Sa, Sb;
    number tmp1, tmp2;

    Sa = getSign(a);
    Sb = getSign(b);

    // aが正 bも正
    if (Sa == 1 && Sb == 1)
    {
        r = preSub(a, b, c);
    }
    // aが正 bは負
    else if (Sa == 1 && Sb == -1)
    {
        getAbs(b, &tmp1);
        r = add(a, &tmp1, c);
    }
    // aが負 bは正
    else if (Sa == -1, Sb == 1)
    {
        getAbs(a, &tmp1);
        r = add(&tmp1, b, c);
        setSign(c, -1);
    }
    // aが負 bも負
    else if (Sa == -1 && Sb == -1)
    {
        getAbs(a, &tmp1);
        getAbs(b, &tmp2);
        r = preSub(&tmp2, &tmp1, c);
    }
    // unexpected
    else
    {
        r = -1;
    }

    return r;
}

//
// b <- a + 1
//
int increment(number *a, number *b)
{
    number one;
    setInt(&one, 1);
    return add(a, &one, b);
}

//
// b <- b - 1
//
int decrement(number *a, number *b)
{
    number one;
    setInt(&one, 1);
    return sub(a, &one, b);
}

//
// int * int 練習
//
int simpleMultiple(int a, int b, int *c)
{
    int cnt = 0;

    *c = a;
    while (1)
    {
        if (cnt == b - 1)
            break;

        if (*c < INT_MAX - a)
            return -1;

        *c += a;

        cnt++;
    }

    return 0;
}

//
// c <- a * b
//
int multiple(const number *a, const number *b, number *c)
{
    int i, j, h, e, r, bi;
    number C, d;

    r = 0;
    clearByZero(&C);
    clearByZero(&d);
    for (i = 0; i < KETA; i++)
    {
        h = 0;

        bi = b->n[i];
        for (j = 0; j < i; j++)
        {
            d.n[j] = 0;
        }
        switch (bi)
        {
        case 0:
            break;

        case 1:
            for (j = 0; j < KETA; j++)
            {
                if (i + j < KETA)
                {
                    d.n[i + j] = a->n[j];
                }
                else if (a->n[j] != 0)
                {
                    r = -1;
                }
            }
            if (add(&C, &d, &C) == -1)
            {
                r = -1;
            }
            break;

        default:
            for (j = 0; j < KETA; j++)
            {
                e = a->n[j] * bi + h;
                h = e / 10;

                if (i + j < KETA)
                {
                    d.n[i + j] = e % 10;
                }
                else if (e != 0)
                {
                    r = -1;
                }
            }
            if (h != 0)
            {
                r = -1;
            }
            if (add(&C, &d, &C) == -1)
            {
                r = -1;
            }
            break;
        }
    }

    setSign(&C, getSign(a) * getSign(b));
    copyNumber(&C, c);

    return r;
}

//
// int / int 練習
//
int simpleDivide(int x, int y, int *z, int *w)
{
    int k;

    if (y == 0)
        return -1;

    k = 0;
    while (1)
    {
        if (x < y)
            break;
        x -= y;
        k++;
    }

    *z = k;
    *w = x;

    return 0;
}

//
// c <- a / b の商
// d <- a / b の剰余
//
int divide(const number *a, const number *b, number *c, number *d)
{
    int signTmp;
    number A, B;

    if (isZero(b) == 0)
        return -1;

    getAbs(a, &A);
    getAbs(b, &B);

    signTmp = getSign(a);
    clearByZero(c);
    while (1)
    {
        if (numComp(&A, &B) == -1)
            break;

        sub(&A, &B, &A);
        increment(c, c);
    }
    copyNumber(&A, d);

    if (isZero(c) == 0)
        setSign(c, 1);
    else
        setSign(c, signTmp * getSign(b));

    if (isZero(d) == 0)
        setSign(d, 1);
    else
        setSign(d, signTmp);

    return 0;
}

//
// c <- a / b の商
// d <- a / b の剰余
//
int divide2(const number *a, const number *b, number *c, number *d)
{
    int comp, signTmp, da, dd, cnt;
    number A, B, e, o, d2;

    if (isZero(b) == 0)
        return -1;

    getAbs(a, &A);
    getAbs(b, &B);

    signTmp = getSign(a);
    clearByZero(c);

    while (numComp(&A, &B) != -1)
    {
        copyNumber(&B, d);

        setInt(&e, 1);
        comp = numComp(&A, d);
        while (comp == 1 || comp == 0)
        {
            mulBy10(d, d);
            mulBy10(&e, &e);
            comp = numComp(&A, d);
        }
        if (comp == -1)
        {
            divBy10(d, d);
            divBy10(&e, &e);
        }
        sub(&A, d, &A);
        add(c, &e, c);
    }
    copyNumber(&A, d);

    if (isZero(c) == 0)
        setSign(c, 1);
    else
        setSign(c, signTmp * getSign(b));

    if (isZero(d) == 0)
        setSign(d, 1);
    else
        setSign(d, signTmp);

    return 0;
}

//
// c <- a / b の商
// d <- a / b の剰余
//
int divide3(const number *a, const number *b, number *c, number *d)
{
    int i, comp, signTmp, da, db, cnt;
    number A, A2, B, e, o, tmp, d2;

    if (isZero(b) == 0)
        return -1;

    getAbs(a, &A);
    getAbs(b, &B);
    clearByZero(c);

    db = getDigit(&B);
    while (numComp(&A, &B) != -1)
    {
        copyNumber(&B, d);

        da = getDigit(&A);
        if (da - db >= 2)
        {
            for (i = db - 1; i >= 0; i--)
            {
                d->n[i + da - db - 1] = d->n[i];
                d->n[i] = 0;
            }
        }
        divide(&A, d, &e, &A);

        if (da - db >= 2)
        {
            e.n[da - db] = e.n[1];
            e.n[1] = 0;
            e.n[da - db - 1] = e.n[0];
            e.n[0] = 0;
        }
        add(c, &e, c);
    }
    copyNumber(&A, d);

    if (isZero(c) == 0)
        setSign(c, 1);
    else
        setSign(c, getSign(a) * getSign(b));

    if (isZero(d) == 0)
        setSign(d, 1);
    else
        setSign(d, getSign(a));

    return 0;
}

//
// Maybe fastest
//
int divide4(const number *a, const number *b, number *c, number *d)
{
    int i, da, da2, db, cnt, signTmp;
    number A, B, e, tmp, d2;

    if (isZero(b) == 0)
        return -1;

    signTmp = getSign(a);
    getAbs(a, &A);
    getAbs(b, &B);
    clearByZero(c);

    db = getDigit(&B);

    while (numComp(&A, &B) != -1)
    {
        copyNumber(&B, d);

        da = getDigit(&A);
        if (da == da2)
        {
            da--;
        }
        da2 = da;

        if (da - db >= 1)
        {
            for (i = db - 1; i >= 0; i--)
            {
                d->n[i + da - db] = d->n[i];
                d->n[i] = 0;
            }
        }

        divide(&A, d, &e, &A);

        if (da - db >= 1)
        {
            e.n[da - db] = e.n[0];
            e.n[0] = 0;
        }

        add(c, &e, c);
    }

    copyNumber(&A, d);

    if (isZero(c) == 0)
        setSign(c, 1);
    else
        setSign(c, signTmp * getSign(b));

    if (isZero(d) == 0)
        setSign(d, 1);
    else
        setSign(d, signTmp);

    return 0;
}

//
// b <- a!
//
int factorial(const number *a, number *b)
{
    number n;

    if (getSign(a) == -1)
    {
        return -2;
    }
    setInt(&n, 1);
    setInt(b, 1);
    while (numComp(a, &n) != 0)
    {
        increment(&n, &n);
        if (multiple(b, &n, b) == -1)
        {
            return -1;
        }
    }
    return 0;
}

//
// b <- \sqrt{a} (単純な引き算)
//
int squareroot(const number *a, number *b)
{
    number N, n, two;

    if (getSign(a) == -1)
        return -1;

    copyNumber(a, &N);
    setInt(&n, 1);
    clearByZero(b);
    setInt(&two, 2);
    while (numComp(&N, &n) != -1)
    {
        sub(&N, &n, &N);
        add(&n, &two, &n);
        increment(b, b);
    }
    return 0;
}

//
// a <- sin(theta) * 10^n
//
int mySin(const number *theta, number *a)
{
    int i, order;
    number n, N, M, ABS, tmp;

    order = 6;
    clearByZero(a);
    setInt(&n, 1);
    copyNumber(theta, &N);
    for (i = 0; i < order; i++)
    {
        mulBy10(&N, &N);
    }

    getAbs(&N, &ABS);
    while (isZero(&ABS) == -1)
    {
        add(a, &N, a);
        multiple(&N, theta, &N);
        multiple(&N, theta, &N);
        increment(&n, &n);
        divide2(&N, &n, &N, &tmp);
        increment(&n, &n);
        divide2(&N, &n, &N, &tmp);

        setSign(&N, getSign(&N) * -1);
        getAbs(&N, &ABS);
        dispNumberZSLN(&N);
    }

    return 0;
}

//
// a <- cos(theta) * 10^n
//
int myCos(const number *theta, number *a)
{
    int i, order;
    number n, N, ABS, zero, tmp;

    order = 90;
    clearByZero(a);
    clearByZero(&zero);
    clearByZero(&n);
    setInt(&N, 1);
    for (i = 0; i < order; i++)
    {
        mulBy10(&N, &N);
    }

    getAbs(&N, &ABS);
    while (numComp(&ABS, &zero) == 1)
    {
        add(a, &N, a);
        multiple(&N, theta, &N);
        multiple(&N, theta, &N);
        increment(&n, &n);
        divide2(&N, &n, &N, &tmp);
        increment(&n, &n);
        divide2(&N, &n, &N, &tmp);

        setSign(&N, getSign(&N) * -1);
        getAbs(&N, &ABS);

        dispNumberZSLN(&N);
    }

    return 0;
}

//
// a <- arcTan(1/x) * 10^n
//
int arcTan2(const number *x, number *a, int order)
{
    int i, sign, cnt;
    number n, xp2, N, M, tmp, abs, two;

    setInt(a, 0);
    setInt(&n, 1);
    setInt(&two, 2);

    // 1 * 10^order
    clearByZero(&N);
    N.n[order] = 1;

    // xp2 = x^2
    copyNumber(x, &xp2);
    multiple(&xp2, x, &xp2);

    // N = 1 * 10^order / x
    divide4(&N, x, &N, &tmp);
    copyNumber(&N, &M);

    sign = 1;

    cnt = 0;
    getAbs(&M, &abs);
    while (isZero(&abs) == -1)
    {
        // a += M
        add(a, &M, a);

        // N = (1 * 10^order / x) / x^2
        divide4(&N, &xp2, &N, &tmp);

        // n += 2
        add(&n, &two, &n);

        // M = N / n
        divide4(&N, &n, &M, &tmp);

        sign *= -1;
        setSign(&M, sign);

        // abs = |M|
        getAbs(&M, &abs);
        cnt++;
    }
    printf("cnt:%d\n", cnt);

    return 0;
}

int arcTan(const number *x, number *a, int order)
{
    int i, cnt;
    number n, xp2, N, M, tmp, abs, two;

    setInt(a, 0);
    setInt(&n, 1);
    setInt(&two, 2);

    // 1 * 10^order
    clearByZero(&N);
    N.n[order] = 1;

    // xp2 = x^2
    copyNumber(x, &xp2);
    multiple(&xp2, x, &xp2);

    // N = 1 * 10^order / x
    divide4(&N, x, &N, &tmp);

    cnt = 0;
    getAbs(&N, &abs);
    while (isZero(&abs) == -1)
    {
        // a += M
        add(a, &N, a);

        multiple(&N, &n, &N);

        // n += 2
        add(&n, &two, &n);

        multiple(&n, &xp2, &M);

        // M = N / n
        divide4(&N, &M, &N, &tmp);

        setSign(&N, getSign(&N) * -1);

        // abs = |M|
        getAbs(&N, &abs);
        cnt++;
    }
    printf("cnt:%d\n", cnt);

    return 0;
}

//
// a <- arcTan(1/x) * 10^n
//
int arcTan3(const number *x, number *a, int order)
{
    int i, sign;
    number n, N, xp2, tmp, abs, bunbo, bunsi, o;

    copyNumber(x, &bunbo);

    setInt(&bunsi, 1);

    // xp2 = x^2
    copyNumber(x, &xp2);
    multiple(&xp2, x, &xp2);

    setInt(&N, -1);

    for (i = 3; i < 300; i += 2)
    {
        setInt(&n, i);
        multiple(&bunsi, &n, &bunsi);
        multiple(&bunsi, &xp2, &bunsi);
        add(&bunsi, &N, &bunsi);

        multiple(&N, &n, &N);
        setSign(&N, getSign(&N) * -1);
        multiple(&bunbo, &xp2, &bunbo);
    }

    getAbs(&N, &abs);
    multiple(&bunbo, &abs, &bunbo);

    // 1 * 10^order
    clearByZero(&o);
    o.n[1300] = 1;
    multiple(&bunsi, &o, &bunsi);

    printf("bunsi: ");
    dispNumberZSLN(&bunsi);
    printf("digit: %d\n", getDigit(&bunsi));

    printf("bunbo: ");
    dispNumberZSLN(&bunbo);
    printf("digit: %d\n", getDigit(&bunbo));

    divide4(&bunsi, &bunbo, a, &tmp);

    return 0;
}
