
#ifndef __DOGGIF_DEF_H_
#define __DOGGIF_DEF_H_

namespace DogGif
{
    /**
    
    
    */

using u8 = unsigned char;
using u16 = unsigned short;

/** ����ͷ
47 49 46 38 39 61
*/
struct GifHead
{
    /** �ļ�����
    */
    u8 signature[3];

    /** �ļ��汾
    */
    u8 version[3];

    bool IsGifFile()
    {
        if (signature[0] != 'G' ||
            signature[1] != 'I' ||
            signature[2] != 'F' ||
            version[0] != '8' ||
            (version[1] != '7' && version[1] != '9') ||
            version[2] == 'a')
        {
            return false;
        }

        return true;
    }
};

/** �߼���Ļ��ʶ��(Logical Screen Descriptor)
f0 00 b4 00 f7 8b 00
*/
struct GifLogicalScreenDescriptor
{
    /** ��ȣ����أ�
    00f0
    */
    u16 m_width;

    /** �߶ȣ����أ�
    00b4
    */
    u16 m_height;

    /** ��ɫ����
    f7 1 111 0 111
        m 7 - ȫ����ɫ�б��־(Global Color Table Flag)������λʱ��ʾ��ȫ����ɫ�б�pixelֵ������.
        cr 6 5 4 - ��ɫ���(Color ResoluTion)��cr+1ȷ��ͼ�����ɫ���.
        s 3 - �����־(Sort Flag)�������λ��ʾȫ����ɫ�б��������.
        pixel 2 1 0 - ȫ����ɫ�б��С��pixel+1ȷ����ɫ�б����������2��pixel+1�η�)
    */
    u8 m_colorDes;

    /** ����ɫ
    8b
        Ϊ������ɫָ��ȫ��ɫ��������ɫ��ָ��Щû�б�ͼ�񸲸ǵ��������ֵ���ɫ����ȫ��ɫ���־λ��Ϊ0������ֶ�Ҳ����ֵ0�����ұ����ԡ�
    */
    u8 m_bgClolr;

    /** ���ؿ�߱�
    00
        ������ֶε�ֵΪ��0�������صĸ߿��������Ĺ�ʽ���㣺
        �߿�� = (���ظ߿�� + 15) / 64
        ���ֶε�ȡֵ��Χ�����ı�ֵ4��1����ߵı�ֵ1��4�������Ĳ���Ϊ1/64��ȡֵ�� 0 - û�б�ֵ��1��255 - ���ڼ����ֵ��
    */
    u8 m_pixelTo;

    /** ȫ����ɫ����ʼλ�� ��14λ
        ȫ����ɫ�б����������߼���Ļ��ʶ�����棬ÿ����ɫ�б�������Ŀ�������ֽ���ɣ���R��G��B��˳�����С�
    */
    u8* m_pGlobalColorTable;
};


/** ��չ��
*/
struct ExtendBlock
{
    /** 0x21 �������һ����չ��
    */
    u8 m_flag;

    /** 0xf9 �������һ��ͼ����չ��
    */
    u8 m_GControlLabel;

    /** ���С �̶�4
    */
    u8 m_blockSize;

    /** �û�������
    */
    u8 m_userFlag;

    /** ����ʱ��
    */
    u16 m_delayTime;

    /** ͸��ɫ����
    */
    u8 m_TranColorIndex;

    /** �ս������ �̶�Ϊ0
    */
    u8 m_endFlag;
};

/** ͼ���ʶ��
    ��������һ������ͼ��ı�ı�Ҫ����������һ��ͼ������ģ�ͼ���ʶ����0x2C(',')�ַ���ʼ��
    һ��ͼ���Ӧһ��ͼ���ʶ����ͼ���ʶ��������Ŷ�Ӧ��ͼ�����ݡ�
*/
struct ImageDescriptor
{
    /** ͼ��Ŀ�ʼ���̶�Ϊ ','
    */
    u8 m_start;

    /** x����ƫ����
    */
    u16 m_xFix;

    /** y����ƫ����
    */
    u16 m_yFix;

    /** ͼ����
    */
    u16 m_width;

    /** ͼ��߶�
    */
    u16 m_height;

    /** �ֲ���ɫ�б���
        m 7 - �ֲ���ɫ�б��־(Local Color Table Flag) ��λʱ��ʶ������ͼ���ʶ��֮����һ���ֲ���ɫ�б�����������֮���һ��ͼ��ʹ�ã�ֵ��ʱʹ��ȫ����ɫ�б�����pixelֵ��
        i 6 - ��֯��־(Interlace Flag)����λʱͼ������ʹ�ý�֯��ʽ���У���ϸ����...��������ʹ��˳�����С�
        s 5 - �����־(Sort Flag)�������λ��ʾ�����ŵľֲ���ɫ�б��������.
        r 4 3 - �����������ʼ��Ϊ0.
        pixel 2 1 0 - �ֲ���ɫ�б��С(Size of Local Color Table)��pixel+1��Ϊ��ɫ�б��λ��
    */
    u8 m_localColorFlag;

    /** �ֲ���ɫ����ʼλ��
    */
    u8* m_pLocalColorTable;
};

/** ͼ���
*/
struct ImageBlock
{
    /**  ͼ���ʶ��
    */
    ImageDescriptor m_imageDescriptor;

    /** ͼ������
    */
    u8 * m_pImageData;
};

/** ������
*/
struct GifDataStream
{
    /** �߼���Ļ��ʶ��(Logical Screen Descriptor)
    */
    GifLogicalScreenDescriptor m_logicalScreenDes;

    /** ͼ���
    */
    ImageBlock m_imageBlock;
};

struct GifTail
{
    /** ';'
    */
    u8 m_endFlag;
};

}

#endif // __DOGGIF_DEF_H_

