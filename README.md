# Enumerando-Informacoes-De-Servicos

Obtendo informações e quantidade de serviços ativos, do sistema de arquivos e driver kernel.
Antes de enumerarmos as informações e serviços, temos que obter a permissão de leitura e enumeração destes, através do gerenciador de serviços do sistema. Para isto, chamamos a função OpenSCManager para solicitar ao gerenciador as permissões necessárias.
Após isto, enumeramos as informações e outros dados.
