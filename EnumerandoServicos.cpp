#include <Windows.h>
#include <winsvc.h>
#include <string>
#include <iostream>
#include <tchar.h>
#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"advapi32.lib")

using namespace std;

class cFuncoes
{
private:

	SC_HANDLE Identificador;

	ENUM_SERVICE_STATUS* Status = 0;

public:

	bool SoliciarAoGerenciador()
	{
		bool bRetorno = false;

		Identificador = OpenSCManager(0, 0, SC_MANAGER_ENUMERATE_SERVICE | SC_MANAGER_CONNECT);

		if (Identificador == NULL)
		{
			cout << "Não foi possível autenticar ao servidor de serviços do sistema..\n";
		}
		else
		{
			bRetorno = true;
		}

		return bRetorno;
	}

	void EnumerarServicos()
	{
		//
		/*
		* Esta função irá enumerar os serviços de kernel e sistema de arquivos, conforme definido na macro SERVICE_DRIVER.
		* Apenas serviços ativos de SERVICE_DRIVER serão enumerados, conforme definido na macro SERVICE_ACTIVE.
		*/
		//
		DWORD BytesRetornados;
		DWORD Servicos;
		DWORD Contagem = 0;
		EnumServicesStatus(Identificador, SERVICE_DRIVER, SERVICE_ACTIVE, 0, 0, &BytesRetornados, &Servicos, &Contagem);
		
		//Iremos alocar a memória obtida na primeira chamada, na matriz ENUM_SERVICE_STATUS.
		Status = (ENUM_SERVICE_STATUS*)malloc(BytesRetornados);

		EnumServicesStatus(Identificador, SERVICE_DRIVER, SERVICE_ACTIVE, Status, BytesRetornados, &BytesRetornados, &Servicos,
			&Contagem);

		int Quantidade = 0;

		for (int i = 0; i < Servicos; i++)
		{
			Quantidade += 1;

			_tprintf(L"Nome: %s\n", Status[i].lpDisplayName);
			_tprintf(L"Serviço: %s\n", Status[i].lpServiceName);

			if (Status[i].ServiceStatus.dwServiceType == SERVICE_FILE_SYSTEM_DRIVER)
			{
				cout << "O serviço é um driver do sistema de arquivos..\n\n";
			}
			else if (Status[i].ServiceStatus.dwServiceType == SERVICE_KERNEL_DRIVER)
			{
				cout << "O serviço é um driver de dispositivo..\n\n";
			}
			else
			{
				cout << "Outro tipo de serviço, consulte documentação para mais informações..\n\n";
			}
		}

		cout << "Quantidade encontrados: " << Quantidade << "\n";

		//Iremos finalizar o identificador, pois não será mais necessário após a busca completa.
		CloseServiceHandle(Identificador);
	}

}Funcoes;

int main()
{

	cout << "O assistente está executando operações de busca no gerenciador de serviços...\n";

	if (Funcoes.SoliciarAoGerenciador() == true)
	{
		cout << "Sucesso ao solicitar..\n";
		cout << "Serviços ativos encontrados..\n\n";
		Funcoes.EnumerarServicos();
	}

	system("pause");
}