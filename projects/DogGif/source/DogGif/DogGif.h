
#ifndef __DOGGIF_H_
#define __DOGGIF_H_

#include "DogGifDef.h"
#include <string>
#include <vector>

namespace DogGifNSP
{

struct DogGifColor
{
    DogGifColor(u8 r, u8 g, u8 b):
        m_r(r),
        m_g(g),
        m_b(b)
    {

    }

    DogGifColor()
    {

    }

    /** red
    */
    u8 m_r = 0;

    /** green
    */
    u8 m_g = 0;

    /** blue
    */
    u8 m_b = 0;
};

struct DogGifFrame
{
    /** �û�������
    */
    u8 m_isNeedUserInput = 0;

    /** ����ʱ��
    */
    u16 m_delayTime = 0;

    /** ͸��ɫ����
        ��λ��ʾʹ��͸����ɫ
    */
    u8 m_tranColorIndex = 0;

    /** x����ƫ����
    */
    u16 m_xFix = 0;

    /** y����ƫ����
    */
    u16 m_yFix = 0;

    /** ͼ����
    */
    u16 m_width = 0;

    /** ͼ��߶�
    */
    u16 m_height = 0;

    /** �Ƿ��оֲ���ɫ��
    */
    u8 m_hasLocalColorTable = 0;

    /** ��֯��־(Interlace Flag)����λʱͼ������ʹ�ý�֯��ʽ���У�����ʹ��˳�����С�
    */
    u8 m_interlaceFlag = 0;

    /** �����־(Sort Flag)�������λ��ʾ�����ŵľֲ���ɫ�б��������.
    */
    u8 m_sortFlag = 0;

    /** �ֲ���ɫ�б���ɫ����
    */
    u16 m_LocalColorTableBit = 0;

    /** �ֲ�ɫ��
    */
    std::vector<DogGifColor> m_localColorTable;

    /** frame����
    */
    std::vector<u8> m_frameData;
};

struct DogGifGolInfo
{
    /** gif��ʶ 
        GIF89a ���� GIF87a
    */
    std::string m_gifHeadSignaturl = "";

    /** ���
    */
    u16 m_width = 0;

    /** �߶ȶ�
    */
    u16 m_height = 0;

    /** �Ƿ���ȫ����ɫ��
    */
    u8 m_hasGolColorTable = 0;

    /** ��ɫ���
    */
    u8 m_colorDepth = 0;

    /** ȫ����ɫ�б��Ƿ��������
    */
    u8 m_isGolColorTableSorted = 0;

    /** ȫ����ɫ�б���ɫ����
    */
    u16 m_golColorTableBit = 0;

    /** ����ɫλ��
    */
    u8 m_bgColorIndex;

    /** ���صĸ߿��
        ������ֶε�ֵΪ��0�������صĸ߿��������Ĺ�ʽ���㣺
        �߿�� = (���ظ߿�� + 15) / 64
        ���ֶε�ȡֵ��Χ�����ı�ֵ4��1����ߵı�ֵ1��4�������Ĳ���Ϊ1/64��ȡֵ�� 0 - û�б�ֵ��1��255 - ���ڼ����ֵ��
    */
    u8 m_pixelToWidthHeight = 0;

    /** ȫ��ɫ��
    */
    std::vector<DogGifColor> m_golColorTable;

    /** ÿһ֡����
    */
    std::vector<DogGifFrame*> m_frameData;

    ~DogGifGolInfo()
    {
        for (auto it : m_frameData)
        {
            delete it;
        }

        m_golColorTable.clear();
    }
};

class DogGif
{
public:
    /** ���캯��
    */
    DogGif();

    /** ��������
    */
    ~DogGif();

public:
    bool Init(u8 * pBuff, u32 buffLen);

private:
    /** ��gifͷ
    @pram [in, out] ppBuff head�Ŀ�ʼָ�룬��ȡ�����Զ�����ƶ���Ӧλ��
    @pram [in, out] buffLen ppBuff���ȣ���ȡ�����Զ����ٶ�ȡ�ĸ���
    @return �Ƿ�ɹ�
    */
    bool ReadHead(u8 ** ppBuff, u32& buffLen);

    /** ��LSD
    @pram [in, out] ppBuff head�Ŀ�ʼָ�룬��ȡ�����Զ�����ƶ���Ӧλ��
    @pram [in, out] buffLen ppBuff���ȣ���ȡ�����Զ����ٶ�ȡ�ĸ���
    @return �Ƿ�ɹ�
    */
    bool ReadLsd(u8 ** ppBuff, u32& buffLen);

    /** ��ȫ��ɫ��
    @pram [in, out] ppBuff head�Ŀ�ʼָ�룬��ȡ�����Զ�����ƶ���Ӧλ��
    @pram [in, out] buffLen ppBuff���ȣ���ȡ�����Զ����ٶ�ȡ�ĸ���
    @return �Ƿ�ɹ�
    */
    bool ReadGolColorTable(u8** ppBuff, u32& buffLen);

    /** ��һ֡
    @pram [in, out] ppBuff head�Ŀ�ʼָ�룬��ȡ�����Զ�����ƶ���Ӧλ��
    @pram [in, out] buffLen ppBuff���ȣ���ȡ�����Զ����ٶ�ȡ�ĸ���
    @return �ɹ�����DogGifFrame���󣬷���NULL
    */
    DogGifFrame* ReadFrameData(u8** ppBuff, u32& buffLen);

private:
    DogGifGolInfo m_gifGolInfo;
};


}
#endif // __DOGGIF_H_

