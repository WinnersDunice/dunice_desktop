#include "checkprocessor.h"


PRAW_SMBIOS_DATA GetSmbiosData()
{
    DWORD bufferSize = 0;

    PRAW_SMBIOS_DATA smbios = NULL;

    // Get required buffer size
    bufferSize = GetSystemFirmwareTable('RSMB', 0, NULL, 0);
    if (bufferSize) {
        smbios = (PRAW_SMBIOS_DATA)LocalAlloc(LPTR, bufferSize);
        bufferSize = GetSystemFirmwareTable('RSMB', 0, (PVOID)smbios, bufferSize);
    }

    return smbios;
}



PSMBIOS_STRUCT_HEADER GetNextStructure(PRAW_SMBIOS_DATA smbios,PSMBIOS_STRUCT_HEADER previous)
{
    PSMBIOS_STRUCT_HEADER next = NULL;
    PBYTE c = NULL;

    // Return NULL is no data found
    if (NULL == smbios)
        return NULL;

    // Return first table if previous was NULL
    if (NULL == previous)
        return (PSMBIOS_STRUCT_HEADER)(&smbios->SMBIOSTableData[0]);

    // Move to the end of the formatted structure
    c = ((PBYTE)previous) + previous->Length;

    // Search for the end of the unformatted structure (\0\0)
    while (true) {
        if ('\0' == *c && '\0' == *(c + 1)) {
            /* Make sure next table is not beyond end of SMBIOS data
             * (Thankyou Microsoft for ommitting the structure count
             * in GetSystemFirmwareTable
             */
            if ((c + 2) < ((PBYTE)smbios->SMBIOSTableData + smbios->Length))
                return (PSMBIOS_STRUCT_HEADER)(c + 2);
            else
                return NULL; // We reached the end
        }

        c++;
    }

    return NULL;
}

PSMBIOS_STRUCT_HEADER GetNextStructureOfType(PRAW_SMBIOS_DATA smbios,PSMBIOS_STRUCT_HEADER previous, DWORD type)
{
    PSMBIOS_STRUCT_HEADER next = previous;
    while (NULL != (next = GetNextStructure(smbios,next))) {
        if (type == next->Type)
            return next;
    }

    return NULL;
}

PSMBIOS_STRUCT_HEADER GetStructureByHandle(PRAW_SMBIOS_DATA smbios,WORD handle)
{
    PSMBIOS_STRUCT_HEADER header = NULL;

    while (NULL != (header = GetNextStructure(smbios,header)))
        if (handle == header->Handle)
            return header;

    return NULL;
}

void GetSmbiosString(PSMBIOS_STRUCT_HEADER table, BYTE index, LPWSTR output, int cchOutput)
{
    DWORD i = 0;
    DWORD len = 0;
    wcscpy(output,L"");

    if (0 == index) return;

    char *c = NULL;

    for (i = 1, c = (char *)table + table->Length; '\0' != *c; c += strlen(c) + 1, i++) {
        if (i == index) {
            len = MultiByteToWideChar(CP_UTF8, 0, c, -1, output,cchOutput);
            break;
        }
    }
}

//вывод значения числового параметра таблицы SMBIOS по указанному смещению
void PrintBiosValue(PRAW_SMBIOS_DATA smbios,DWORD type,DWORD offset, DWORD size)
{
    PSMBIOS_STRUCT_HEADER head=NULL;
    PBYTE cursor = NULL;

    head = GetNextStructureOfType(smbios,head, type);
    if (NULL == head){ printf("PrintBiosValue Error!\n");return;}

    cursor=((PBYTE)head+offset);

    //value
    for(int i=0;i<size;i++) {
        printf("%02x",(unsigned int) *cursor);
        cursor++;
    }
    printf("\n");
}

//вывод значения строкового параметра таблицы SMBIOS по указанному смещению
void PrintBiosString(PRAW_SMBIOS_DATA smbios,DWORD type,DWORD offset)
{
    PSMBIOS_STRUCT_HEADER head;
    head=NULL;
    PBYTE cursor = NULL;
    WCHAR buf[1024];

    head = GetNextStructureOfType(smbios,head, type);
    if (NULL == head){printf("PrintString Error!\n");return;}
    cursor=((PBYTE)head+offset);
    BYTE val=*cursor;

    GetSmbiosString((head), *cursor,buf,1024);
    //  value
    wprintf(L"%s\n",buf);
}
