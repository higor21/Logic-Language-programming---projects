#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>

#define MAX_NOME 51
#define MAX_Q_ALUNOS 100

using namespace std;


struct Aluno{
    char nome[MAX_NOME];
    int matricula;
    float notas[4];
    int n_faltas;
};

void abrir_dados(Aluno alunos[], int matriz[][MAX_Q_ALUNOS], int &n_alunos);
void salvar_dados(Aluno alunos[], int matriz[][MAX_Q_ALUNOS], int n_alunos); /// SALVAR ALUNOS E MATRIZ EM alunos.txt E relacao.txt, RESPECTIVAMENTE
int existencia_aluno(Aluno alunos[], int n_alunos, int matricula); /// VERIFICA SE HÁ ALGUMA ALUNO COM A MATRÍCULA DADA
void consulta_matricula(Aluno alunos[], int n_alunos, int matricula);
void consulta_nome(Aluno alunos[], int n_alunos, char nome[], int vet_indices[], int &q_alunos);
void inserir_aluno(Aluno alunos[], int &n_alunos, int matriz[][MAX_Q_ALUNOS], char nome[]);
void excluir_aluno(Aluno alunos[], int &n_alunos, int matriz[][MAX_Q_ALUNOS], int matricula);
void inserir_nota(Aluno alunos[], int n_alunos, int matricula);
void inserir_falta(Aluno alunos[], int n_alunos, int matricula);
void inserir_relacao(Aluno alunos[], int n_alunos, int matricula_aluno1, int matricula_aluno2, int matriz[][MAX_Q_ALUNOS]);
int media_faltas(Aluno alunos[], int n_alunos);
void exibir_histograma(Aluno alunos[], int n_alunos);
void listar_relacao(Aluno alunos[], int n_alunos, int matricula, int matriz[][MAX_Q_ALUNOS]);
void verificar_relacao(Aluno alunos[], int n_alunos, int matricula_aluno1, int matricula_aluno2, int matriz[][MAX_Q_ALUNOS]);


/// FUNÇÕES AUXILIARES
void menu();
void imprimir_aluno(Aluno A);
void pegar_dados_aluno(Aluno &A);
int gerar_matricula();

int main()
{
    Aluno alunos[MAX_Q_ALUNOS];
    int matriz[MAX_Q_ALUNOS][MAX_Q_ALUNOS], n_alunos = 0, opcao;

    /// VARIAVEIS AUXILIARES
    char nome[MAX_NOME];
    int matricula, matricula_aux;

    /// LEITURA DOS ARQUIVOS
    abrir_dados(alunos,matriz,n_alunos);

    do{
        system("PAUSE");
        system("cls");
        menu();
        cin>>opcao;
        switch(opcao){
        case 0: /// CONSULTA POR NOME
            cout<<"\nCONSULTA POR NOME:\n\nINFORME O NOME DO ALUNO: ";
            int vet_id[MAX_Q_ALUNOS], tam;
            cin.ignore();
            cin.getline(nome,MAX_NOME);
            consulta_nome(alunos,n_alunos,nome,vet_id,tam);
            if(tam == 0)
                cout<<"Nome nao encontrado!\n";
            while(--tam >= 0){
                cout<<"\n\n";
                imprimir_aluno(alunos[vet_id[tam]]);
                cout<<"\n\n";
            }
            break;
        case 1: /// CONSULTA POR MATRICULA
            cout<<"\nCONSULTA POR MATRICULA:\n\nINFORME A MATRICULA DO ALUNO: ";
            cin>>matricula;
            cout<<"\n\n";
            consulta_matricula(alunos,n_alunos,matricula);
            cout<<"\n\n";
            break;
        case 2: /// INSERCAO DE UM NOVO ALUNO
            cout<<"\nINSERCAO DE UM NOVO ALUNO:\n\nINFORME O NOME DO ALUNO: ";
            cin.ignore();
            cin.getline(nome,MAX_NOME);
            inserir_aluno(alunos,n_alunos,matriz,nome);
            break;
        case 3: /// REMOCAO DE UM ALUNO
            cout<<"\nREMOCAO DE UM ALUNO:\n\nINFORME A MATRICULA DO ALUNO: ";
            cin>>matricula;
            excluir_aluno(alunos,n_alunos,matriz,matricula);
            break;
        case 4: /// INSERCAO DE UMA NOTA
            cout<<"\nINSERCAO DE UMA NOTA:\n\nINFORME A MATRICULA DO ALUNO: ";
            cin>>matricula;
            inserir_nota(alunos,n_alunos,matricula);
            break;
        case 5: /// INSERCAO DE UMA FALTA
            cout<<"\nINSERCAO DE UMA FALTA:\n\nINFORME A MATRICULA DO ALUNO: ";
            cin>>matricula;
            inserir_falta(alunos,n_alunos,matricula);
            break;
        case 6: /// ATRICUICAO DE RELACAO ENTRE ALUNOS
            cout<<"\nATRIBUICAO DE RELACAO ENTRE ALUNOS:\n\nINFORME A MATRICULA DO PRIMEIRO ALUNO: ";
            cin>>matricula;
            cout<<"\nINFORME A MATRICULA DO SEGUNDO ALUNO: ";
            cin>>matricula_aux;
            inserir_relacao(alunos,n_alunos,matricula,matricula_aux,matriz);
            break;
        case 7: /// MEDIA DAS FALTAS DOS ALUNOS
            cout<<"MEDIA DAS FALTAS DOS ALUNOS: "<<media_faltas(alunos,n_alunos)<<"\n\n";
            break;
        case 8: /// HISTOGRAMA
            cout<<"\nHISTOGRAMA DOS ALUNOS: \n";
            exibir_histograma(alunos,n_alunos);
            break;
        case 9: /// LISTAGEM DOS ALUNOS QUE ESTAO RELACIONADOS COM UM ALUNO
            cout<<"\nLISTAGEM DOS ALUNOS QUE ESTAO RELACIONADOS COM UM ALUNO:\n\nINFORME A MATRICULA DO ALUNO: ";
            cin>>matricula;
            listar_relacao(alunos,n_alunos,matricula,matriz);
            break;
        case 10: /// RELACAO ENTRE DOIS ALUNOS
            cout<<"\nVERIFICAR RELACAO ENTRE ALUNOS:\n\nINFORME A MATRICULA DO PRIMEIRO ALUNO: ";
            cin>>matricula;
            cout<<"\nINFORME A MATRICULA DO SEGUNDO ALUNO: ";
            cin>>matricula_aux;
            verificar_relacao(alunos,n_alunos,matricula,matricula_aux,matriz);
            break;
        case 11: /// SAIR DO PROGRAMA
            cout<<"\n\nSAINDO DO PROGRAMA, SUAS ALTERACOES SERAO SALVAS!\n\n";
            break;
        default:
            cout<<"\nOpcao invalida!\n";
       }
    }while(opcao != 11);

    /// SALVANDO DADOS
    salvar_dados(alunos,matriz,n_alunos);

    return 0;
}

/// FUNÇÕES AUXILIARES

void menu(){
    cout<<"\nTODAS AS OPCOES:\n\n";
    cout<<"(0) CONSULTA POR NOME\n";
    cout<<"(1) CONSULTA POR MATRICULA\n";
    cout<<"(2) INSERCAO DE UM NOVO ALUNO\n";
    cout<<"(3) REMOCAO DE UM ALUNO\n";
    cout<<"(4) INSERCAO DE UMA NOTA\n";
    cout<<"(5) INSERCAO DE UMA FALTA\n";
    cout<<"(6) ATRIBUICAO DE RELACAO ENTRE ALUNOS\n";
    cout<<"(7) MEDIA DAS FALTAS DOS ALUNOS\n";
    cout<<"(8) EXIBIR HISTOGRAMA\n";
    cout<<"(9) RELACAO DOS ALUNOS COM O ALUNO i\n";
    cout<<"(10) RELACAO ENTRE DOIS ALUNOS\n";
    cout<<"(11) SAIR DO PROGRAMA\n";
    cout<<"\nOpcao: ";
}

void imprimir_aluno(Aluno A){
    cout<<"nome: "<<A.nome<<"\nmatricula: "<<A.matricula<<"\nnotas: ";
    for(int k=0; k<3; k++)
        cout<<A.notas[k]<<((k!=2) ? ' ' : '\n');
    cout<<"n faltas: "<<A.n_faltas;
}

int gerar_matricula(){
    srand(time(NULL));
    return rand()%INT_MAX; /// MAXIMO VALOR DE UM INTEIRO
}

/// FUNÇÕES SOLICITADAS

void verificar_relacao(Aluno alunos[], int n_alunos, int matricula_aluno1, int matricula_aluno2, int matriz[][MAX_Q_ALUNOS]){
    int i = existencia_aluno(alunos,n_alunos,matricula_aluno1), j = existencia_aluno(alunos,n_alunos,matricula_aluno2);
    if(i == j){
        cerr<<"Alunos contendo mesma matricula!\n";
        return;
    }else if(i == -1 || j == -1){
        cerr<<"\nUma/duas das matriculas informadas nao existe!\n";
        return;
    }
    switch(matriz[i][j]){
    case 0:
        cout<<"\nRelacao: NAO SE CONHECEM\n";
        break;
    case 1:
        cout<<"\nRelacao: CONHECEM-SE DE VISTA\n";
        break;
    case 2:
        cout<<"\nRelacao: SAO AMIGOS\n";
        break;
    default:
        cout<<"\nRelacao Invalida!\n"; /// NUNCA DEVE CAIR NESTE CASO: SÓ PARA TESTE DE POSSÍVEL ERRO DO PROGRAMADOR KKKK
    }
}

void listar_relacao(Aluno alunos[], int n_alunos, int matricula, int matriz[][MAX_Q_ALUNOS]){
    int i = existencia_aluno(alunos,n_alunos,matricula), status;
    if(i == -1){
        cerr<<"Aluno nao existente!\n";
        return;
    }
    cout<<"\nINFORME O status DA RELACAO:\n* 0: NAO SE CONHECEM\n* 1:CONHECEM-SE DE VISTA\n * : SAO AMIGOS\n\nResposta: ";
    do{
        cin>>status;
    }while(status<0 || status>2);
    cout<<"\n\nALUNOS RELACIONADOS COM "<<alunos[i].nome<<":\n\n";
    for(int k=0; k<n_alunos; k++)
        if(matriz[i][k] == status){
            imprimir_aluno(alunos[k]);
            cout<<"\n\n";
        }
}

void exibir_histograma(Aluno alunos[], int n_alunos){
    float vet_classes[10] = {}, media = 0.0;
    int max_n_medias = 0, indice;
    for(int i=0; i<n_alunos; i++){
        indice = int ((alunos[i].notas[0] + alunos[i].notas[1] + alunos[i].notas[2])/3.0);
        vet_classes[(indice != 10) ? indice : 9]++;
        if(max_n_medias <= vet_classes[indice])
            max_n_medias = vet_classes[indice];
    }
    /// IMPRESSAO
    while(max_n_medias >= -1){
        if(max_n_medias >= 0){
            if(max_n_medias != 0){
                cout<<max_n_medias<<":\t";
                for(int i=0; i<10; i++)
                    ((vet_classes[i] >= max_n_medias) ? cout<<"  |   " : cout<<"      ");
                cout<<endl;
            }
        }else{
            cout<<"\t____________________________________________________________\n";
            cout<<"\t [0,1[ [1,2[ [2,3[ [3,4[ [4,5[ [5,6[ [6,7[ [7,8[ [8,9[ [9,10]\n";
        }
        max_n_medias--;
    }
}

int media_faltas(Aluno alunos[], int n_alunos){
    int q_faltas = 0, i = n_alunos;
    while(--i >= 0){
        q_faltas += alunos[i].n_faltas;
    }
    return q_faltas/n_alunos;
}

void inserir_relacao(Aluno alunos[], int n_alunos, int matricula_aluno1, int matricula_aluno2, int matriz[][MAX_Q_ALUNOS]){
    int i = existencia_aluno(alunos,n_alunos,matricula_aluno1), j = existencia_aluno(alunos,n_alunos,matricula_aluno2), status;
    if(i == j){
        cerr<<"Alunos contendo mesma matricula!\n";
        return;
    }else if(i == -1 || j == -1){
        cerr<<"\nUma/duas das matriculas informadas nao existe!\n";
        return;
    }
    cout<<"\nINFORME A NOVA RELACAO ENTRE OS ALUNOS:\n*(0) NAO SE CONHECEM\n*(1) SE CONHECEM, MAS NAO SE RELACIONAM\n*(2) SE RELACIONAM BASTANTE\n\nResposta: ";
    do{ cin>>status; }while(status<0 || status>2);
    matriz[i][j] = matriz[j][i] = status;
    cout<<"\nRelacao adicionada com sucesso!\n";
}

void inserir_falta(Aluno alunos[], int n_alunos, int matricula){
    int i = existencia_aluno(alunos,n_alunos,matricula), q_faltas;
    if(i == -1){
        cerr<<"Aluno nao existente!\n";
        return;
    }
    cout<<"\nQUANTAS FALTAS SERAO INSERIDAS: ";
    cin>>q_faltas;
    (alunos[i].n_faltas + q_faltas < 0) ? alunos[i].n_faltas = 0 : alunos[i].n_faltas += q_faltas;
    cout<<"\nFalta adicionada com sucesso!";
}

void inserir_nota(Aluno alunos[], int n_alunos, int matricula){
    int i = existencia_aluno(alunos,n_alunos,matricula), unidade;
    if(i == -1){
        cerr<<"Aluno nao existente!\n";
        return;
    }
    cout<<"\nINFORME A UNIDADE PARA INSERCAO DA NOTA:\n* UNID 1\n* UNID 2\n* UNID 3\n\nResposta: ";
    do{
        cin>>unidade;
    }while(unidade>3 || unidade<1);
    cout<<"\nAGORA INFORME A NOTA: ";
    do{
        cin>>alunos[i].notas[unidade-1];
    }while(alunos[i].notas[unidade-1]<0 || alunos[i].notas[unidade-1]>10);
    cout<<"\nNota adicionada com sucesso!\n";
}

void inserir_aluno(Aluno alunos[], int &n_alunos, int matriz[][MAX_Q_ALUNOS], char nome[]){
    int new_matricula;
    if(n_alunos < MAX_Q_ALUNOS){
        do{
            new_matricula = gerar_matricula();
        }while(existencia_aluno(alunos,n_alunos, new_matricula) != -1);

        strcpy(alunos[n_alunos].nome,nome);
        alunos[n_alunos].matricula = new_matricula;
        for(int i=0; i<4; i++)
            alunos[n_alunos].notas[i] = 0;
        alunos[n_alunos].n_faltas = 0;

        for(int k = 0; k <(n_alunos+1); k++)
            matriz[n_alunos][k] = matriz[k][n_alunos] = 0;
        n_alunos++;
        cout<<"\nInsercao do aluno com sucesso! Sua matricula é "<<new_matricula<<"\n";
    }else
        cerr << "\nCapacidade de maxima alunos!\n";
}

void excluir_aluno(Aluno alunos[], int &n_alunos, int matriz[][MAX_Q_ALUNOS], int matricula){
    if(n_alunos == 0){
        cerr<<"\nVetor contem 0 alunos!\n";
        return;
    }
    int pos = existencia_aluno(alunos,n_alunos,matricula);
    if(pos == -1){
        cerr<<"Aluno nao existente na disciplina!\n";
        return;
    }

    for(int k1 = 0; k1 < n_alunos ; k1++){
        for(int k2 = pos; k2 < n_alunos-1 ; k2++){
            matriz[k1][k2] = matriz[k1][k2+1]; /// ALTERANDO COLUNAS
            matriz[k2][k1] = matriz[k2+1][k1]; /// ALTERANDO LINHAS
            if(k1 == 0) alunos[k2] = alunos[k2+1];
        }
    }
    n_alunos--;
    cout<<"Exito na exclusao do aluno!\n";
}

void consulta_nome(Aluno alunos[], int n_alunos, char nome[] , int vet_indices[], int &q_alunos){
    q_alunos = 0;
    for(int i=0; i<n_alunos; i++)
        if(strcmp(alunos[i].nome,nome) == 0)
            vet_indices[q_alunos++] = i;
}

void consulta_matricula(Aluno alunos[], int n_alunos, int matricula){
    int i = existencia_aluno(alunos, n_alunos, matricula);
    if(i != -1){
        imprimir_aluno(alunos[i]);
        return;
    }
    cerr<<"Matricula nao existente!\n";
}

int existencia_aluno(Aluno alunos[], int n_alunos, int matricula){
    for(int i=0; i<n_alunos; i++)
        if(alunos[i].matricula == matricula)
            return i;
    return -1;
}

void salvar_dados(Aluno alunos[], int matriz[][MAX_Q_ALUNOS], int n_alunos){
    ofstream outfile_alunos, outfile_relacao;

    outfile_alunos.open("alunos.txt");
    outfile_alunos<<n_alunos<<endl;
    for(int i=0; i<n_alunos; i++){
        outfile_alunos<<alunos[i].nome<<'\n'<<alunos[i].matricula<<'\n';
        for(int k=0; k<3; k++)
            outfile_alunos<<alunos[i].notas[k]<<((k!=2) ? ' ' : '\n');
        outfile_alunos<<alunos[i].n_faltas<<'\n';
    }
    outfile_alunos.close();

    outfile_relacao.open("relacao.txt");
    outfile_relacao<<n_alunos<<' '<<n_alunos<<'\n';
    for(int i=0; i<n_alunos; i++)
        for(int j=0; j<n_alunos; j++)
            outfile_relacao<<matriz[i][j]<<((j != n_alunos-1) ? ' ' : '\n');
    outfile_relacao.close();
}

void abrir_dados(Aluno alunos[], int matriz[][MAX_Q_ALUNOS], int &n_alunos){
    fstream infile_alunos, infile_relacao;

    int aux;

    infile_alunos.open("alunos.txt");
    infile_alunos>>n_alunos;
    for(int i=0; i<n_alunos; i++){
        infile_alunos.ignore();
        infile_alunos.getline(alunos[i].nome,MAX_NOME);
        infile_alunos>>alunos[i].matricula;
        for(int k=0; k<3; k++)
            infile_alunos>>alunos[i].notas[k];
        infile_alunos>>alunos[i].n_faltas;
    }
    infile_alunos.close();

    infile_relacao.open("relacao.txt");
    infile_relacao>>aux;
    infile_relacao>>aux;
    for(int i=0; i<n_alunos; i++)
        for(int j=0; j<n_alunos; j++)
            infile_relacao>>matriz[i][j];
    infile_relacao.close();
}



























