#ifndef CHECKPROCESSOR_H
#define CHECKPROCESSOR_H

#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

// SMBIOS Table Type numbers
#define SMB_TABLE_BIOS              0
#define SMB_TABLE_SYSTEM            1
#define SMB_TABLE_BASEBOARD         2
#define SMB_TABLE_CHASSIS           3
#define SMB_TABLE_PROCESSOR         4
#define SMB_TABLE_MEMCTRL           5
#define SMB_TABLE_MEMMODULES        6
#define SMB_TABLE_PORTS             8
#define SMB_TABLE_SLOTS             9
#define SMB_TABLE_OEM_STRINGS       11
#define SMB_TABLE_SYS_CFG_OPTIONS   12
#define SMB_TABLE_MEM_ARRAY         16
#define SMB_TABLE_MEM_DEVICE        17
#define SMB_TABLE_END_OF_TABLE      127

// 64bit Word type
typedef unsigned long long QWORD;

/*
* Structures
*/
typedef struct _RawSmbiosData
{
    BYTE    Used20CallingMethod;
    BYTE    SMBIOSMajorVersion;
    BYTE    SMBIOSMinorVersion;
    BYTE    DmiRevision;
    DWORD   Length;
    BYTE    SMBIOSTableData[1];
} RAW_SMBIOS_DATA, * PRAW_SMBIOS_DATA;

typedef struct _SmbiosStructHeader
{
    BYTE Type;
    BYTE Length;
    WORD Handle;
} SMBIOS_STRUCT_HEADER, * PSMBIOS_STRUCT_HEADER;

// Structures
typedef struct _NODE {
    wchar_t* Name;                      // Name of the node
    struct _NODE_ATT_LINK* Attributes;  // Array of attributes linked to the node
    struct _NODE* Parent;               // Parent node
    struct _NODE_LINK* Children;        // Array of linked child nodes
    int Flags;                          // Node configuration flags
} NODE, * PNODE;

typedef struct _NODE_LINK {
    struct _NODE* LinkedNode;           // Node attached to this node
} NODE_LINK, * PNODE_LINK;

typedef struct _NODE_ATT {
    wchar_t* Key;                       // Attribute name
    wchar_t* Value;                     // Attribute value string (may be null separated multistring if NAFLG_ARRAY is set)
    int Flags;                          // Attribute configuration flags
} NODE_ATT, * PNODE_ATT;

typedef struct _NODE_ATT_LINK {
    struct _NODE_ATT* LinkedAttribute;  // Attribute linked to this node
} NODE_ATT_LINK, * PNODE_ATT_LINK;


/********************************************************************/


class CheckProcessor
{

private:

    PRAW_SMBIOS_DATA GetSmbiosData();
    PSMBIOS_STRUCT_HEADER GetNextStructure(PRAW_SMBIOS_DATA smbios,PSMBIOS_STRUCT_HEADER previous);
    PSMBIOS_STRUCT_HEADER GetNextStructureOfType(PRAW_SMBIOS_DATA smbios,PSMBIOS_STRUCT_HEADER previous, DWORD type);
    PSMBIOS_STRUCT_HEADER GetStructureByHandle(PRAW_SMBIOS_DATA smbios,WORD handle);

public:
    CheckProcessor();

    //вывод значения числового параметра таблицы SMBIOS по указанному смещению
    void GetSmbiosString(PSMBIOS_STRUCT_HEADER table, BYTE index, LPWSTR output, int cchOutput);
    //вывод значения строкового параметра таблицы SMBIOS по указанному смещению
    void PrintBiosString(PRAW_SMBIOS_DATA smbios,DWORD type,DWORD offset);
};

#endif // CHECKPROCESSOR_H
