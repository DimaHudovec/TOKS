#include "ports.h"

bool Init_COM1()
{
	ZeroMemory(&dcb,sizeof(DCB));
	LPCWSTR  lpFileName = TEXT("COM1");
	hCom_1 = CreateFile(lpFileName,						//открываемый файл
						GENERIC_READ | GENERIC_WRITE,	//задаём тип доступа к файлу
						0,								//задаём параметры совместного доступа(для коммуникационных поротов = 0)
						NULL,							//атрибуты защиты порта(для коммуникационных портов = NULL)
						OPEN_EXISTING,					//режим автосохранения(для коммуникационных портов = OPEN_EXISTING)
						0,								//атрибуты создаваемого файла(0 - синхронная работа, FILE_FLAG_OVERLAPPED – асинхронная)
						NULL);							//задаёт описатель файла шаблона(для коммуникационных портов = NULL)

	if(hCom_1 == INVALID_HANDLE_VALUE) //если порт не удалось открыть
		return false;

	if(!GetCommState(hCom_1, &dcb)) //если не удалось получить статус порта
	{
		CloseHandle(hCom_1);
		return false;
	}

	//настра иваем параметры порта
	dcb.BaudRate = CBR_9600;				//скорость передачи 9600 бод
	dcb.ByteSize = 8;						//разме рбайта данных
	dcb.StopBits = ONESTOPBIT;				//один стоповый бит
	dcb.Parity = NOPARITY;					//нет контроля чётности
	dcb.DCBlength = sizeof(DCB);			//в первое поле структуры DCB необходимо занести её длину
	dcb.fBinary = TRUE;						//включаем двоичный режим обмена
	dcb.fOutxCtsFlow = FALSE;				//выключаем режим слежения за сигналом CTS
	dcb.fOutxDsrFlow = FALSE;				//выключаем режим слежения за сигналом DSR
	dcb.fDtrControl = DTR_CONTROL_DISABLE;	//отключаем использование линии DTR
	dcb.fDsrSensitivity = FALSE;			//отключаем восприимчивость драйвера к состоянию линии DSR
	dcb.fNull = FALSE;						//разрешить приём нулевых байтов
	dcb.fRtsControl = RTS_CONTROL_DISABLE;	//отключаем использование линии RTS
	dcb.fAbortOnError = FALSE;				//отключаем остановку всех операций чтения/записи при ошибке

	if(! SetCommState(hCom_1, &dcb)) //сохраняем новые параметры конфигурации
	{
		CloseHandle(hCom_1);
		return false;
	}


	//установить размеры очередей приёма и передачи
	//SetupComm(hCom_1,2000,2000);
	//PurgeComm(hCom_1, PURGE_RXCLEAR);	//очистить принимающий буфер порта


	return true;
}

bool Init_COM2()
{
	ZeroMemory(&dcb,sizeof(DCB));
	LPCWSTR  lpFileName = TEXT("COM2");
	hCom_2 = CreateFile(lpFileName,						//открываемый файл
						GENERIC_READ | GENERIC_WRITE,	//задаём тип доступа к файлу
						0,								//задаём параметры совместного доступа(для коммуникационных поротов = 0)
						NULL,							//атрибуты защиты порта(для коммуникационных портов = NULL)
						OPEN_EXISTING,					//режим автосохранения(для коммуникационных портов = OPEN_EXISTING)
						0,								//атрибуты создаваемого файла(0 - синхронная работа, FILE_FLAG_OVERLAPPED – асинхронная)
						NULL);							//задаёт описатель файла шаблона(для коммуникационных портов = NULL)

	if(hCom_2 == INVALID_HANDLE_VALUE) //если порт не удалось открыть
		return false;

	if(!GetCommState(hCom_2, &dcb)) //если не удалось получить статус порта
	{
		CloseHandle(hCom_2);
		return false;
	}

	//настра иваем параметры порта
	dcb.BaudRate = CBR_4800;				//скорость передачи 9600 бод
	dcb.ByteSize = 8;						//разме рбайта данных
	dcb.StopBits = ONESTOPBIT;				//один стоповый бит
	dcb.Parity = NOPARITY;					//нет контроля чётности
	dcb.DCBlength = sizeof(DCB);			//в первое поле структуры DCB необходимо занести её длину
	dcb.fBinary = TRUE;						//включаем двоичный режим обмена
	dcb.fOutxCtsFlow = FALSE;				//выключаем режим слежения за сигналом CTS
	dcb.fOutxDsrFlow = FALSE;				//выключаем режим слежения за сигналом DSR
	dcb.fDtrControl = DTR_CONTROL_DISABLE;	//отключаем использование линии DTR
	dcb.fDsrSensitivity = FALSE;			//отключаем восприимчивость драйвера к состоянию линии DSR
	dcb.fNull = FALSE;						//разрешить приём нулевых байтов
	dcb.fRtsControl = RTS_CONTROL_DISABLE;	//отключаем использование линии RTS
	dcb.fAbortOnError = FALSE;				//отключаем остановку всех операций чтения/записи при ошибке

	if(! SetCommState(hCom_1, &dcb)) //сохраняем новые параметры конфигурации
	{
		CloseHandle(hCom_1);
		return false;
	}


	//установить размеры очередей приёма и передачи
	//SetupComm(hCom_1,2000,2000);
	//PurgeComm(hCom_1, PURGE_RXCLEAR);	//очистить принимающий буфер порта


	return true;
}
/*запись данных в порт*/
bool WriteDataCOM(char* buf)
{

	DWORD dwBytesWrite;
	WriteFile(hCom_1, buf, strlen(buf) + 1, &dwBytesWrite, NULL);
	if (strncmp(buf, "exit", 4) == 0)
		return false;
	return true;
}

/*чтение данных из порта*/
//bool ReadDataCOM()
//{
//	char readChar;
//	DWORD dwBytesRead;
//	char buffer[256] = "";
//	int i = 0;
//	while (ReadFile(hCom_2, &readChar, 1, &dwBytesRead, NULL) == true)
//	{
//		buffer[i++] = readChar;
//		if (readChar == '\0') {
//			cout << buffer;
//			if (strncmp(buffer, "exit", 4) == 0)
//				return false;
//			return true;
//		}
//	}
//	return false;
//}

void CloseCOM()
{
	if(hCom_1)
	{
		CloseHandle(hCom_1);
		hCom_1 = NULL;
	}
}
