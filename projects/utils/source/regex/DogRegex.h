
#ifndef __DOGREGEX_H_
#define __DOGREGEX_H_

//////////////////////////////////////////////////////////////////////////
//                         һЩ���õ�������ʽ                             //
//                         �����ο�������                                  //
//////////////////////////////////////////////////////////////////////////

#include "typedef/DogString.h"

/** ���֣�
*/
static const DogChar* s_regex_number = _DogT(R"([0-9]*)");

/** nλ������
*/
static const DogChar* s_regex_n_number = _DogT(R"(\d{n})");

/** ����nλ������
*/
static const DogChar* s_regex_np_number = _DogT(R"(\d{n,})");

/** m-nλ�����֣�
*/
static const DogChar* s_regex_nm_number = _DogT(R"(\d{n,m})");

/** �㿪ͷ������
*/
static const DogChar* s_regex_0_number = _DogT(R"((0[0-9]*))");

/** ���㿪ͷ������
*/
static const DogChar* s_regex_n0_number = _DogT(R"(([1-9][0-9]*))");

/** ���㿪ͷ������mλС��������
*/
static const DogChar* s_regex_n0_mdcml_number = _DogT(R"(([1-9][0-9]*)+(\.[0-9]{1,m})?)");

/** ����mλС���ĸ���
*/
static const DogChar* s_regex_nativ_mdcml_number = _DogT(R"((\-)?\d+(\.\d{1,m})?)");

/** ������
*/
static const DogChar* s_regex_q_number = _DogT(R"((\-|\+)?\d+(\.\d+)?)");

/** ����
*/
static const DogChar* s_regex_chinese = _DogT(R"([\u4e00-\u9fa5]+)");

/** Ӣ�ĺ�����
*/
static const DogChar* s_regex_comm_char = _DogT(R"([A-Za-z0-9]+)");

/** Email��ַ��?
*/
static const DogChar* s_regex_email = _DogT(R"([a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\.[a-zA-Z0-9_-]+)+)");

/** ������?
*/
static const DogChar* s_regex_domain_name = _DogT(R"(\w+(\.\w)+)";

#endif //__DOGREGEX_H_
