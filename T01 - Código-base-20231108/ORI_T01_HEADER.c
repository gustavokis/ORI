/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Organização de Recuperação da Informação
 * Prof. Tiago A. Almeida
 *
 * Trabalho 01 - Indexação
 * Gustavo Sanches Martins Kis - 801319
 * ========================================================================== *
 *   <<< IMPLEMENTE AQUI!!! COPIE E COLE O CONTEÚDO DESTE ARQUIVO NO AVA >>>
 * ========================================================================== */

/* Bibliotecas */
#include "ORI_T01_HEADER.h"

/* ===========================================================================
 * ================================= FUNÇÕES ================================= */


/* <<< COLOQUE AQUI OS DEMAIS PROTÓTIPOS DE FUNÇÕES, SE NECESSÁRIO >>> */


/* Funções auxiliares para o qsort.
 * Com uma pequena alteração, é possível utilizá-las no bsearch, assim, evitando código duplicado.
 * */

/* Função de comparação entre chaves do índice corredores_idx */
int qsort_corredores_idx(const void *a, const void *b) {
    return strcmp( ( (corredores_index *)a )->id_corredor, ( (corredores_index *)b )->id_corredor);
}

/* Função de comparação entre chaves do índice veiculos_idx */
int qsort_veiculos_idx(const void *a, const void *b) {
	return strcmp( ( (veiculos_index *)a )->id_veiculo, ( (veiculos_index *)b )->id_veiculo);
}

/* Função de comparação entre chaves do índice pistas_idx */
int qsort_pistas_idx(const void *a, const void *b) {
	return strcmp( ( (pistas_index *)a )->id_pista, ( (pistas_index *)b )->id_pista);
}

/* Função de comparação entre chaves do índice corridas_idx */
int qsort_corridas_idx(const void *a, const void *b) {
	if(strcmp( ( (corridas_index *)a )->ocorrencia, ( (corridas_index *)b )->ocorrencia) == 0){
		return strcmp( ( (corridas_index *)a )->id_pista, ( (corridas_index *)b )->id_pista);
	}	
	else{
		return strcmp( ( (corridas_index *)a )->ocorrencia, ( (corridas_index *)b )->ocorrencia);
	}
}

/* Funções de comparação apenas entre data de ocorrencia do índice corridas_idx */
int qsort_data_idx(const void *a, const void *b){
	return strcmp( ( (corridas_index *)a )->ocorrencia, ( (corridas_index *)b )->ocorrencia);
}

/* Função de comparação entre chaves do índice nome_pista_idx */
int qsort_nome_pista_idx(const void *a, const void *b){
	return strcmp( ( (nome_pista_index *)a )->nome, ( (nome_pista_index *)b )->nome);
}

/* Função de comparação entre chaves do índice preco_veiculo_idx */
int qsort_preco_veiculo_idx(const void *a, const void *b){
	if((((preco_veiculo_index *)a )->preco) < (( (preco_veiculo_index *)b )->preco)){
		return -1;
	}else if((((preco_veiculo_index *)a )->preco) > (( (preco_veiculo_index *)b )->preco)){
		return 1;
	}
	return 0;
}

/* Função de comparação entre chaves do índice secundário de corredor_veiculos_secundario_idx */
int qsort_corredor_veiculos_secundario_idx(const void *a, const void *b){
	return strcmp( ( (corredor_veiculos_secundario_index *)a )->chave_secundaria, ( (corredor_veiculos_secundario_index *)b )->chave_secundaria);
}

/* Cria o índice respectivo */
void criar_corredores_idx() {
    if (!corredores_idx)
        corredores_idx = malloc(MAX_REGISTROS * sizeof(corredores_index));
 
    if (!corredores_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }
 
    for (unsigned i = 0; i < qtd_registros_corredores; ++i) {
        Corredor c = recuperar_registro_corredor(i);
 
        if (strncmp(c.id_corredor, "*|", 2) == 0)
            corredores_idx[i].rrn = -1; // registro excluído
        else
            corredores_idx[i].rrn = i;
 
        strcpy(corredores_idx[i].id_corredor, c.id_corredor);
    }
 
    qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
    printf(INDICE_CRIADO, "corredores_idx");
}

void criar_veiculos_idx() {
	if (!veiculos_idx)
        veiculos_idx = malloc(MAX_REGISTROS * sizeof(veiculos_index));
 
    if (!veiculos_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }
 
    for (unsigned i = 0; i < qtd_registros_veiculos; ++i) {
        Veiculo v = recuperar_registro_veiculo(i);
        veiculos_idx[i].rrn = i;
        strcpy(veiculos_idx[i].id_veiculo, v.id_veiculo);
    }
 
    qsort(veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx);
    printf(INDICE_CRIADO, "veiculos_idx");
}

void criar_pistas_idx() {
	if (!pistas_idx){
        pistas_idx = malloc(MAX_REGISTROS * sizeof(pistas_index));
	}
    if (!pistas_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }
 
    for (unsigned i = 0; i < qtd_registros_pistas; ++i) {
        Pista p = recuperar_registro_pista(i);
        pistas_idx[i].rrn = i; 
        strcpy(pistas_idx[i].id_pista, p.id_pista);
    }
 
    qsort(pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx);
    printf(INDICE_CRIADO, "pistas_idx");
}

void criar_corridas_idx() {
    if (!corridas_idx){
        corridas_idx = malloc(MAX_REGISTROS * sizeof(corridas_index));
	}
    if (!corridas_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }
	for (unsigned i = 0; i < qtd_registros_corridas;++i){
		Corrida cor = recuperar_registro_corrida(i);
		corridas_idx[i].rrn = i; 
		strcpy(corridas_idx[i].id_pista, cor.id_pista);
		strcpy(corridas_idx[i].ocorrencia, cor.ocorrencia);
	}
    qsort(corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_corridas_idx);
    printf(INDICE_CRIADO, "corridas_idx");
}

void criar_nome_pista_idx() {
    if (!nome_pista_idx){
        nome_pista_idx = malloc(MAX_REGISTROS * sizeof(nome_pista_index));
	}
    if (!nome_pista_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }
 
    for (unsigned i = 0; i < qtd_registros_pistas; ++i) {
        Pista np = recuperar_registro_pista(i);
  
        strcpy(nome_pista_idx[i].id_pista, np.id_pista);

		strcpy(nome_pista_idx[i].nome, strupr(np.nome));
    }
 
    qsort(nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx);
    printf(INDICE_CRIADO, "nome_pista_idx");
}

void criar_preco_veiculo_idx() {
    	if (!preco_veiculo_idx)
        preco_veiculo_idx = malloc(MAX_REGISTROS * sizeof(preco_veiculo_index));
 
    if (!preco_veiculo_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }
 
    for (unsigned i = 0; i < qtd_registros_veiculos; ++i) {
        Veiculo pv = recuperar_registro_veiculo(i);
 
        strcpy(preco_veiculo_idx[i].id_veiculo, pv.id_veiculo);
		preco_veiculo_idx[i].preco = pv.preco;
    }
 
    qsort(preco_veiculo_idx, qtd_registros_veiculos, sizeof(preco_veiculo_index), qsort_preco_veiculo_idx);
    printf(INDICE_CRIADO, "preco_veiculo_idx");
}

void criar_corredor_veiculos_idx() {
	if (!corredor_veiculos_idx.corredor_veiculos_secundario_idx){
        corredor_veiculos_idx.corredor_veiculos_secundario_idx = 
		malloc(MAX_REGISTROS * sizeof(corredor_veiculos_secundario_index));
	}
    if (!corredor_veiculos_idx.corredor_veiculos_primario_idx){
        corredor_veiculos_idx.corredor_veiculos_primario_idx = 
		malloc(MAX_REGISTROS * sizeof(corredor_veiculos_primario_index));
	}
    if (!corredor_veiculos_idx.corredor_veiculos_primario_idx || !corredor_veiculos_idx.corredor_veiculos_secundario_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    for (unsigned i = 0; i < qtd_registros_corredores; ++i) {
		Corredor c = recuperar_registro_corredor(i);
	
		for(int k = 0; k < QTD_MAX_VEICULO; k++) {
			if(strlen(c.veiculos[k]) > 0) {
				strupr(c.veiculos[k]);
				inverted_list_insert(c.veiculos[k],c.id_corredor,&corredor_veiculos_idx);
			}	  
		}
	}	   
    
    printf(INDICE_CRIADO, "corredor_veiculos_idx");
}

/* Exibe um registro com base no RRN */
bool exibir_corredor(int rrn) {
    if (rrn < 0){
		printf (ERRO_ARQUIVO_VAZIO);
        return false;
	}
    Corredor c = recuperar_registro_corredor(rrn);
 
    printf("%s, %s, %s, %s, %.2lf\n", c.id_corredor, c.nome, c.apelido, c.cadastro, c.saldo);
    return true;
}

bool exibir_veiculo(int rrn) {
    if (rrn < 0){
		printf (ERRO_ARQUIVO_VAZIO);
        return false;
	}
    Veiculo v = recuperar_registro_veiculo(rrn);
 
    printf("%s, %s, %s, %s, %d, %d, %d, %.2lf\n", v.id_veiculo, v.marca, v.modelo, v.poder, v.velocidade,v.aceleracao,v.peso,v.preco);
    return true;
}

bool exibir_pista(int rrn) {
	if (rrn < 0){
		printf (ERRO_ARQUIVO_VAZIO);
        return false;
	}
    Pista p = recuperar_registro_pista(rrn);
 
    printf("%s, %s, %d, %d, %d\n", p.id_pista, p.nome, p.dificuldade, p.distancia, p.recorde);
    return true;
}

bool exibir_corrida(int rrn) {
	if (rrn < 0){
		printf (ERRO_ARQUIVO_VAZIO);
        return false;
	}
    Corrida cor = recuperar_registro_corrida(rrn);
 
    printf("%s, %s, %s, %s\n", cor.id_pista, cor.ocorrencia, cor.id_corredores, cor.id_veiculos);
    return true;
}

/* Recupera do arquivo o registro com o RRN informado
 * e retorna os dados nas structs corredor, Curso e Inscricao */
Corredor recuperar_registro_corredor(int rrn) {
	Corredor c;
	char temp[TAM_REGISTRO_CORREDOR + 1], *p;
	strncpy(temp, ARQUIVO_CORREDORES + (rrn * TAM_REGISTRO_CORREDOR), TAM_REGISTRO_CORREDOR);
	temp[TAM_REGISTRO_CORREDOR] = '\0';

	p = strtok(temp, ";");
	strcpy(c.id_corredor, p);
	p = strtok(NULL, ";");
	strcpy(c.nome, p);
	p = strtok(NULL, ";");
	strcpy(c.apelido, p);
	p = strtok(NULL, ";");
	strcpy(c.cadastro, p);
	p = strtok(NULL, ";");
	c.saldo = atof(p);
	p = strtok(NULL, ";");

	for(int i = 0; i < QTD_MAX_VEICULO; ++i)
		c.veiculos[i][0] = '\0';

	if(p[0] != '#') {
		p = strtok(p, "|");

		for(int pos = 0; p; p = strtok(NULL, "|"), ++pos)
			strcpy(c.veiculos[pos], p);
	}

	return c;
}

Veiculo recuperar_registro_veiculo(int rrn) {
	Veiculo v;
	char temp[TAM_REGISTRO_VEICULO + 1], *p;
	strncpy(temp, ARQUIVO_VEICULOS + (rrn * TAM_REGISTRO_VEICULO), TAM_REGISTRO_VEICULO);
	temp[TAM_REGISTRO_VEICULO] = '\0';

	p = strtok(temp, ";");
	strcpy(v.id_veiculo, p);
	p = strtok(NULL, ";");
	strcpy(v.marca, p);
	p = strtok(NULL, ";");
	strcpy(v.modelo, p);
	p = strtok(NULL, ";");
	strcpy(v.poder, p);
	p = strtok(NULL, ";");
	v.velocidade = atoi(p);
	p = strtok(NULL, ";");
	v.aceleracao = atoi(p);
	p = strtok(NULL, ";");
	v.peso = atoi(p);
	p = strtok(NULL, ";");
	v.preco = atof(p);
	p = strtok(NULL, ";");
	
	return v;
}

Pista recuperar_registro_pista(int rrn) {
	Pista p;
	char temp[TAM_REGISTRO_PISTA + 1], *po;
	strncpy(temp, ARQUIVO_PISTAS + (rrn * TAM_REGISTRO_PISTA), TAM_REGISTRO_PISTA);
	temp[TAM_REGISTRO_PISTA] = '\0';

	po = strtok(temp, ";");
	strcpy(p.id_pista, po);
	po = strtok(NULL, ";");
	strcpy(p.nome, po);
	po = strtok(NULL, ";");
	p.dificuldade = atoi(po);
	po = strtok(NULL, ";");
	p.distancia = atoi(po);
	po = strtok(NULL, ";");
	p.recorde = atoi(po);
	po = strtok(NULL, ";");

	return p;
}

Corrida recuperar_registro_corrida(int rrn) {
	Corrida c;

	char temp[TAM_REGISTRO_CORRIDA - 1];
	strncpy(temp, ARQUIVO_CORRIDAS + (rrn * TAM_REGISTRO_CORRIDA), TAM_REGISTRO_CORRIDA);
	temp[TAM_REGISTRO_CORRIDA] = '\0';

	strncpy(c.id_pista, temp,TAM_ID_PISTA - 1);
	c.id_pista[TAM_ID_PISTA - 1] = '\0';
	strncpy(c.ocorrencia, temp + TAM_ID_PISTA - 1, TAM_DATETIME -1);
	c.ocorrencia[TAM_DATETIME - 1] = '\0';
	strncpy(c.id_corredores, temp + TAM_ID_PISTA + TAM_DATETIME - 2, TAM_ID_CORREDORES -1);
	c.id_corredores[TAM_ID_CORREDORES - 1] = '\0';
	strncpy(c.id_veiculos, temp + TAM_ID_PISTA + TAM_DATETIME + TAM_ID_CORREDORES - 3, TAM_ID_VEICULOS - 1);
	c.id_veiculos[TAM_ID_VEICULOS - 1] = '\0';
	return c;
}

/* Escreve em seu respectivo arquivo na posição informada (RRN) */
void escrever_registro_corredor(Corredor c, int rrn) {
	char temp[TAM_REGISTRO_CORREDOR + 1], p[100];
	temp[0] = '\0'; p[0] = '\0';

	strcpy(temp, c.id_corredor);
	strcat(temp, ";");
	strcat(temp, c.nome);
	strcat(temp, ";");
	strcat(temp, c.apelido);
	strcat(temp, ";");
	strcat(temp, c.cadastro);
	strcat(temp, ";");
	sprintf(p, "%013.2lf", c.saldo);
	strcat(temp, p);
	strcat(temp, ";");

	for(int i = 0, k = 0; i < QTD_MAX_VEICULO; i++) {
		if(strlen(c.veiculos[i]) > 0) {
			if (k == 0){
				k = 1;
			}else{
				strcat(temp, "|");
			}	
			strcat(temp, c.veiculos[i]);
		}
	}
	strcat(temp, ";");

	strpadright(temp, '#', TAM_REGISTRO_CORREDOR);

	strncpy(ARQUIVO_CORREDORES + rrn*TAM_REGISTRO_CORREDOR, temp, TAM_REGISTRO_CORREDOR);
}

void escrever_registro_veiculo(Veiculo v, int rrn) {
	char temp[TAM_REGISTRO_VEICULO + 1], p[100];
	temp[0] = '\0'; p[0] = '\0';

	strcpy(temp, v.id_veiculo);
	strcat(temp, ";");
	strcat(temp, v.marca);
	strcat(temp, ";");
	strcat(temp, v.modelo);
	strcat(temp, ";");
	strcat(temp, v.poder);
	strcat(temp, ";");
	sprintf(p, "%04d", v.velocidade);
	strcat(temp, p);
	strcat(temp, ";");
	sprintf(p, "%04d", v.aceleracao);
	strcat(temp, p);
	strcat(temp, ";");
	sprintf(p, "%04d", v.peso);
	strcat(temp, p);
	strcat(temp, ";");
	sprintf(p, "%013.2lf", v.preco);
	strcat(temp, p);
	strcat(temp, ";");

	strpadright(temp, '#', TAM_REGISTRO_VEICULO);

	strncpy(ARQUIVO_VEICULOS + rrn*TAM_REGISTRO_VEICULO, temp, TAM_REGISTRO_VEICULO);
}

void escrever_registro_pista(Pista p, int rrn) {
	char temp[TAM_REGISTRO_PISTA + 1], po[100];
	temp[0] = '\0'; po[0] = '\0';

	strcpy(temp, p.id_pista);
	strcat(temp, ";");
	strcat(temp, p.nome);
	strcat(temp, ";");
	sprintf(po, "%04d", p.dificuldade);
	strcat(temp, po);
	strcat(temp, ";");
	sprintf(po, "%04d", p.distancia);
	strcat(temp, po);
	strcat(temp, ";");
	sprintf(po, "%04d", p.recorde);
	strcat(temp, po);
	strcat(temp, ";");

	strpadright(temp, '#', TAM_REGISTRO_PISTA);

	strncpy(ARQUIVO_PISTAS + rrn*TAM_REGISTRO_PISTA, temp, TAM_REGISTRO_PISTA);
}

void escrever_registro_corrida(Corrida i, int rrn) {
	char temp[TAM_REGISTRO_CORRIDA + 1];
	temp[0] = '\0';

	strncpy(temp, i.id_pista, TAM_ID_PISTA);
	temp[TAM_ID_PISTA - 1] = '\0';
	strncat(temp, i.ocorrencia,TAM_DATETIME);
	temp[TAM_ID_PISTA + TAM_DATETIME - 2] = '\0';
	strncat(temp, i.id_corredores,TAM_ID_CORREDORES);
	temp[TAM_ID_PISTA + TAM_DATETIME + TAM_ID_CORREDORES - 3] = '\0';
	strncat(temp, i.id_veiculos,TAM_ID_VEICULOS);
	temp[TAM_ID_PISTA + TAM_DATETIME + TAM_ID_CORREDORES + TAM_ID_VEICULOS - 4] = '\0';

	strncpy(ARQUIVO_CORRIDAS + rrn*TAM_REGISTRO_CORRIDA, temp, TAM_REGISTRO_CORRIDA);
}

/* Funções principais */
void cadastrar_corredor_menu(char *id_corredor, char *nome, char *apelido){
	corredores_index index;
	strcpy(index.id_corredor,id_corredor);
	corredores_index *found = busca_binaria((void*)&index, corredores_idx,
	qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	if(found != NULL && found->rrn>=0){
		printf(ERRO_PK_REPETIDA,id_corredor);
	} else{
		Corredor c;
		strcpy(c.id_corredor,id_corredor);
		strcpy(c.nome,nome);
		strcpy(c.apelido,apelido);
		c.saldo = 0.0;
		char data[TAM_DATETIME];
		current_datetime(data);
		strcpy(c.cadastro, data);
		for(int s = 0; s < QTD_MAX_VEICULO;s++){
			c.veiculos[s][0] = '\0';
		}
		escrever_registro_corredor(c,qtd_registros_corredores);
		strcpy(corredores_idx[qtd_registros_corredores].id_corredor,
		c.id_corredor);
		corredores_idx[qtd_registros_corredores].rrn = qtd_registros_corredores;
		qtd_registros_corredores++;
    	qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index),
		qsort_corredores_idx);
		printf(SUCESSO);
	}
}

void remover_corredor_menu(char *id_corredor) {
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
	corredores_index *found = busca_binaria((void*)&index, corredores_idx,
	qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	if(found == NULL || found->rrn < 0){
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	} else{
		Corredor co = recuperar_registro_corredor(found->rrn);
		co.id_corredor[0] = '*';
		co.id_corredor[1] = '|';
		escrever_registro_corredor(co,found->rrn);
		found->rrn = -1;
		printf(SUCESSO);
	}
}

void adicionar_saldo_menu(char *id_corredor, double valor) {
	adicionar_saldo(id_corredor, valor, true);
}

void adicionar_saldo(char *id_corredor, double valor, bool flag){
	corredores_index *found = busca_binaria((void*)id_corredor, corredores_idx,
	qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	if(found == NULL || found->rrn < 0){
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	} else{
		if(valor <= 0){
			printf(ERRO_VALOR_INVALIDO);
		}else{
			Corredor cor = recuperar_registro_corredor(found->rrn);
			cor.saldo += valor;
			escrever_registro_corredor(cor,found->rrn);
			if (flag){				
				printf(SUCESSO);
			}	
		}
	}
}

void comprar_veiculo_menu(char *id_corredor, char *id_veiculo) {
	corredores_index *found1 = busca_binaria((void*)id_corredor, corredores_idx,
	qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	if(found1 == NULL || found1->rrn < 0){
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	}else{
		veiculos_index *found2 = busca_binaria((void*)id_veiculo, veiculos_idx,
		qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);
		if(found2 == NULL || found2->rrn < 0){
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}else{
			Corredor c = recuperar_registro_corredor(found1->rrn);
			Veiculo v = recuperar_registro_veiculo(found2->rrn);
			if(c.saldo < v.preco){
				printf(ERRO_SALDO_NAO_SUFICIENTE);
				return;
			}else{
				int k = 0;
				int j = 0;
				for(int i = 0; i < QTD_MAX_VEICULO; i++){
					if(strcmp(c.veiculos[i],v.modelo) == 0){
						printf(ERRO_VEICULO_REPETIDO,c.id_corredor,v.id_veiculo);
						return;
					}
					if(strlen(c.veiculos[i]) > 0){
						k++;
					}
					if(strlen(c.veiculos[i]) == 0){
						j = 1;
						i = QTD_MAX_VEICULO;
					}
				}
				if(j == 1){	
					strcpy(c.veiculos[k],v.modelo);
					c.saldo = c.saldo - v.preco;
					escrever_registro_corredor(c,found1->rrn);
					strupr(c.veiculos[k]);	
					inverted_list_insert(c.veiculos[k],c.id_corredor,&corredor_veiculos_idx);	
				}
				printf(SUCESSO);
			}
		}
	}
}

void cadastrar_veiculo_menu(char *marca, char *modelo, char *poder, int velocidade, int aceleracao, int peso, double preco) {
	char c[TAM_ID_VEICULO];
	c[TAM_ID_VEICULO-1] = '\0';
	sprintf(c,"%07d",qtd_registros_veiculos);
	veiculos_index *found = busca_binaria((void*)c, veiculos_idx,
	qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);

	if(found != NULL){
		printf(ERRO_PK_REPETIDA,c);
	} else{
		Veiculo v;
		strcpy(v.id_veiculo,c);
		strcpy(v.marca,marca);
		strcpy(v.modelo,modelo);
		strcpy(v.poder,poder);
		v.velocidade = velocidade;
		v.aceleracao = aceleracao;
		v.peso = peso;
		v.preco = preco;
		escrever_registro_veiculo(v,qtd_registros_veiculos);
		strcpy(veiculos_idx[qtd_registros_veiculos].id_veiculo,
		c);
		veiculos_idx[qtd_registros_veiculos].rrn = qtd_registros_veiculos;
		strcpy(preco_veiculo_idx[qtd_registros_veiculos].id_veiculo,c);
		preco_veiculo_idx[qtd_registros_veiculos].preco = preco;
		qtd_registros_veiculos++;
    	qsort(veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index),
		qsort_veiculos_idx);
		qsort(preco_veiculo_idx, qtd_registros_veiculos, sizeof(preco_veiculo_index),
		qsort_preco_veiculo_idx);
		printf(SUCESSO);
	}
}

void cadastrar_pista_menu(char *nome, int dificuldade, int distancia, int recorde){
	nome_pista_index nom;
	strupr(strcpy(nom.nome,nome));
	pistas_index *found = busca_binaria((void*)nom.nome, nome_pista_idx->nome,
	qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx, false, 0);
	if(found && found->rrn >= 0){
		printf(ERRO_PK_REPETIDA,nome);
	} else{
		Pista p;
		strcpy(p.nome,nome);
		p.dificuldade = dificuldade;
		p.distancia = distancia;
		p.recorde = recorde;
		char c[TAM_ID_PISTA];
		c[TAM_ID_PISTA-1] = '\0';
		sprintf(c,"%08d",qtd_registros_pistas);
		strcpy(p.id_pista,c);
		escrever_registro_pista(p,qtd_registros_pistas);
		strcpy(pistas_idx[qtd_registros_pistas].id_pista,
		c);
		pistas_idx[qtd_registros_pistas].rrn = qtd_registros_pistas;
		strcpy(nome_pista_idx[qtd_registros_pistas].id_pista,c);
		strcpy(nome_pista_idx[qtd_registros_pistas].nome,nom.nome);
		qtd_registros_pistas++;
    	qsort(pistas_idx, qtd_registros_pistas, sizeof(pistas_index),
		qsort_pistas_idx);
		qsort(nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index),
		qsort_nome_pista_idx);
		printf(SUCESSO);
	}
}

void executar_corrida_menu(char *id_pista, char *ocorrencia, char *id_corredores, char *id_veiculos) {
	int k = 0;
	corridas_index ch;
	strcpy(ch.id_pista, id_pista);
	strcpy(ch.ocorrencia, ocorrencia);
	corridas_index *foundcomp = busca_binaria((void*)&ch, corridas_idx,
	qtd_registros_corridas, sizeof(corridas_idx), qsort_corridas_idx, false, 0);
	if(foundcomp != NULL){
		char cc[21];
		strcpy(cc,ocorrencia);
		strcat(cc,id_pista);
		printf(ERRO_PK_REPETIDA,cc);
		return;
	}else if (foundcomp == NULL){
		pistas_index *foundp = busca_binaria((void*)id_pista, pistas_idx,
		qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, false, 0);
		if(foundp == NULL){
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}else{
			corredores_index co[6];
			veiculos_index ve[6];
			for(unsigned i = 0; i < 6; i++){
				Corredor c;
				Veiculo v;
				strncpy(ve[i].id_veiculo, id_veiculos + 7*i, 7);
				ve[i].id_veiculo[7] = '\0';
				strncpy(co[i].id_corredor, id_corredores + 11*i, 11);
				co[i].id_corredor[11] = '\0';
				corredores_index *foundc = busca_binaria((void*)co[i].id_corredor, corredores_idx,
				qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
				veiculos_index *foundv = busca_binaria((void*)ve[i].id_veiculo, veiculos_idx,
				qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);
				if(foundc == NULL || foundv == NULL || foundc->rrn < 0){
					printf(ERRO_REGISTRO_NAO_ENCONTRADO);
					return;
				}else{
					c = recuperar_registro_corredor(foundc->rrn);
					v = recuperar_registro_veiculo(foundv->rrn);
					int m;
					int j = 0;
					for(m = 0; m < QTD_MAX_VEICULO; m++){
						if(strcmp(c.veiculos[m],v.modelo) == 0){
							j = 1;
						}
					}
					if(j != 1){
						printf(ERRO_CORREDOR_VEICULO,c.id_corredor,v.id_veiculo);
						k = 1;
					}
				}
			}
			if (k == 0){
			Pista p = recuperar_registro_pista(foundp->rrn);
			int premio = 6 * (TX_FIXA * p.dificuldade);
			adicionar_saldo(co[0].id_corredor,((premio/10)*4),false);
			adicionar_saldo(co[1].id_corredor,((premio/10)*3),false);
			adicionar_saldo(co[2].id_corredor,((premio/10)*2),false);
			Corrida cori;
			strcpy(cori.id_pista,id_pista);
			strcpy(cori.ocorrencia,ocorrencia);
			strcpy(cori.id_corredores,id_corredores);
			strcpy(cori.id_veiculos,id_veiculos);
			escrever_registro_corrida(cori,qtd_registros_corridas);
			corridas_idx[qtd_registros_corridas].rrn = qtd_registros_corridas;
			strcpy(corridas_idx[qtd_registros_corridas].id_pista,id_pista);
			strcpy(corridas_idx[qtd_registros_corridas].ocorrencia,ocorrencia);
			qtd_registros_corridas++;
			qsort(corridas_idx, qtd_registros_corridas, sizeof(corridas_index),
			qsort_corridas_idx);
			printf(SUCESSO);
			}
		}
	}
}
/* Busca */
void buscar_corredor_id_menu(char *id_corredor) {
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
    corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, true, 0);
	if (found == NULL || found->rrn < 0)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_corredor(found->rrn);
}

void buscar_pista_id_menu(char *id_pista) {
	pistas_index index;
	strcpy(index.id_pista, id_pista);
    pistas_index *found = busca_binaria((void*)&index, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, true, 0);
	if (found == NULL || found->rrn < 0)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_pista(found->rrn);
}

void buscar_pista_nome_menu(char *nome_pista) {
	nome_pista_index index;
	strcpy(index.nome, strupr(nome_pista));
    nome_pista_index *found = busca_binaria((void*)&index, nome_pista_idx, 
	qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx, true, 0);
	if (found == NULL || found->id_pista == NULL)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else{
		buscar_pista_id_menu(found->id_pista);
	}	
}

/* Listagem */
void listar_corredores_id_menu() {
	if (qtd_registros_corredores == 0)
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	else
		for (unsigned int i = 0; i < qtd_registros_corredores; i++)
			exibir_corredor(corredores_idx[i].rrn);
}

void listar_corredores_modelo_menu(char *modelo){
	int chaveS = 0;
	strupr(modelo);
	if(inverted_list_secondary_search(&chaveS,0,modelo,&corredor_veiculos_idx)){
		char ind[MAX_REGISTROS][TAM_ID_CORREDOR];
		int p = inverted_list_primary_search(ind,true,chaveS,NULL,&corredor_veiculos_idx);
		if(p == 0){
			printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
			return;
		}else{
			qsort(ind, p, TAM_ID_CORREDOR,qsort_string_modelo);
			for(int i = 0; i < p;i++){
				corredores_index *found = busca_binaria((void*)&ind[i], corredores_idx, 
				qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
				if(found == NULL){
					printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
				}else{
					exibir_corredor(found->rrn);
				}	
			}
		}

	}else{
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	}

	
}

void listar_veiculos_compra_menu(char *id_corredor) {
	corredores_index *found = busca_binaria((void*)id_corredor, corredores_idx, 
	qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	if(found == NULL || found->rrn < 0){
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	}else{
		Corredor c = recuperar_registro_corredor(found->rrn);
		preco_veiculo_index ind;
		ind.preco = c.saldo;
		strcpy(ind.id_veiculo,"\0");
		preco_veiculo_index *found2 = busca_binaria((void*)&ind, preco_veiculo_idx, 
		qtd_registros_veiculos, sizeof(preco_veiculo_index), qsort_preco_veiculo_idx, false, 1);
		if(found2 == NULL || found2->id_veiculo == NULL){
			printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
		}else{
		preco_veiculo_index *index = &preco_veiculo_idx[0];
		while (index < found2){
			veiculos_index vel;
			strcpy(vel.id_veiculo,index->id_veiculo);
			vel.rrn = -1;
			veiculos_index *found3 = busca_binaria((void*)&vel, veiculos_idx, 
			qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);
			exibir_veiculo(found3->rrn);
			index++;
		}
		}
	}
}

void listar_corridas_periodo_menu(char *data_inicio, char *data_fim) {
	corridas_index *found1 = busca_binaria((void*)data_inicio, corridas_idx, 
	qtd_registros_corridas, sizeof(corridas_index), qsort_corridas_idx, true, 1);
	corridas_index *found2= busca_binaria((void*)data_fim, corridas_idx, 
	qtd_registros_corridas, sizeof(corridas_index), qsort_corridas_idx, false, -1);
	if(found1 == NULL || found2 == NULL){
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	}else{
	do{
		exibir_corrida(found1->rrn);
		found1++;
	}while (found1<=found2);
	}
}

/* Liberar espaço */
void liberar_espaco_menu() {
	int j = 0;
	char cor[TAM_ARQUIVO_CORREDORES];
	cor[0]='\0';
	for (int i = 0; i < qtd_registros_corredores;i++){
		Corredor c = recuperar_registro_corredor(i);
		if(strncmp(c.id_corredor , "*|", 2) != 0){
			strncpy(cor + (TAM_REGISTRO_CORREDOR*j),ARQUIVO_CORREDORES + i*TAM_REGISTRO_CORREDOR,
			TAM_REGISTRO_CORREDOR);
			corredores_idx[j].rrn = j;
			strcpy(corredores_idx[j].id_corredor, c.id_corredor);
			j++;
		}
	}
	qtd_registros_corredores = j;
	qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index),
	qsort_corredores_idx);
	strcpy(ARQUIVO_CORREDORES,cor);
	printf(SUCESSO);
}

/* Imprimir arquivos de dados */
void imprimir_arquivo_corredores_menu() {
	if (qtd_registros_corredores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORREDORES);
}

void imprimir_arquivo_veiculos_menu() {
	if (qtd_registros_veiculos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_VEICULOS);
}

void imprimir_arquivo_pistas_menu() {
	if (qtd_registros_pistas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_PISTAS);
}

void imprimir_arquivo_corridas_menu() {
	if (qtd_registros_corridas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORRIDAS);
}

/* Imprimir índices primários */
void imprimir_corredores_idx_menu() {
	if (corredores_idx == NULL || qtd_registros_corredores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_corredores; ++i)
			printf("%s, %d\n", corredores_idx[i].id_corredor, corredores_idx[i].rrn);
}

void imprimir_veiculos_idx_menu() {
	if (veiculos_idx == NULL || qtd_registros_veiculos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_veiculos; ++i)
			printf("%s, %d\n", veiculos_idx[i].id_veiculo, veiculos_idx[i].rrn);
}

void imprimir_pistas_idx_menu() {
	if (pistas_idx == NULL || qtd_registros_pistas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_pistas; ++i)
			printf("%s, %d\n", pistas_idx[i].id_pista, pistas_idx[i].rrn);
}

void imprimir_corridas_idx_menu() {
	if (corridas_idx == NULL || qtd_registros_corridas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_corridas; ++i)
			printf("%s, %s, %d\n", corridas_idx[i].ocorrencia, corridas_idx[i].id_pista, corridas_idx[i].rrn);
		

}

/* Imprimir índices secundários */
void imprimir_nome_pista_idx_menu() {
	if (nome_pista_idx == NULL || qtd_registros_pistas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_pistas; ++i)
			printf("%s, %s\n", nome_pista_idx[i].nome, nome_pista_idx[i].id_pista);
}

void imprimir_preco_veiculo_idx_menu() {
	if (preco_veiculo_idx == NULL || qtd_registros_veiculos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_veiculos; ++i)
			printf("%.2lf, %s\n", preco_veiculo_idx[i].preco, preco_veiculo_idx[i].id_veiculo);
}

void imprimir_corredor_veiculos_secundario_idx_menu() {
	if (corredor_veiculos_idx.corredor_veiculos_secundario_idx == NULL 
	|| corredor_veiculos_idx.qtd_registros_secundario == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < corredor_veiculos_idx.qtd_registros_secundario; ++i)
			printf("%s, %d\n", corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].chave_secundaria,
			corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].primeiro_indice);
}

void imprimir_corredor_veiculos_primario_idx_menu(){
	if (corredor_veiculos_idx.corredor_veiculos_primario_idx == NULL 
	|| corredor_veiculos_idx.qtd_registros_primario == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < corredor_veiculos_idx.qtd_registros_primario; ++i)
			printf("%s, %d\n", corredor_veiculos_idx.corredor_veiculos_primario_idx[i].chave_primaria,
			corredor_veiculos_idx.corredor_veiculos_primario_idx[i].proximo_indice);
}

/* Liberar memória e encerrar programa */
void liberar_memoria_menu() {
	free(corredores_idx);
	free(veiculos_idx);
	free(pistas_idx);
	free(corridas_idx);
	free(nome_pista_idx);
	free(preco_veiculo_idx);
	free(corredor_veiculos_idx.corredor_veiculos_primario_idx);
	free(corredor_veiculos_idx.corredor_veiculos_secundario_idx);
}

void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t) {

    int pInicial;
    char chaveS[t->tam_chave_secundaria + 1];	
	chaveS[t->tam_chave_secundaria] = '\0';
    strcpy(chaveS, chave_secundaria);
    bool encontrado = inverted_list_secondary_search(&pInicial, 0, chaveS, t);

    if (!encontrado){
        strcpy(t->corredor_veiculos_secundario_idx[t->qtd_registros_secundario].chave_secundaria, chaveS);
        t->corredor_veiculos_secundario_idx[t->qtd_registros_secundario].primeiro_indice = 
		t->qtd_registros_primario;
		t->qtd_registros_secundario++;
		qsort(t->corredor_veiculos_secundario_idx, t->qtd_registros_secundario, 
		sizeof(corredor_veiculos_secundario_index),
		qsort_corredor_veiculos_secundario_idx);
		strcpy(t->corredor_veiculos_primario_idx[t->qtd_registros_primario].chave_primaria, chave_primaria);
    	t->corredor_veiculos_primario_idx[t->qtd_registros_primario].proximo_indice = -1;
    }
    else{
        int pFinal;
        inverted_list_primary_search(NULL, 0, pInicial, &pFinal, t);
		strcpy(t->corredor_veiculos_primario_idx[t->qtd_registros_primario].chave_primaria, chave_primaria);
        t->corredor_veiculos_primario_idx[pFinal].proximo_indice = t->qtd_registros_primario;
		t->corredor_veiculos_primario_idx[t->qtd_registros_primario].proximo_indice = -1;
    }
    t->qtd_registros_primario++;
}

bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t) {
	corredor_veiculos_secundario_index index;
	strcpy(index.chave_secundaria,chave_secundaria);
	corredor_veiculos_secundario_index *cor = busca_binaria(&index, 
	t->corredor_veiculos_secundario_idx, t->qtd_registros_secundario,
    sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx,
    exibir_caminho, 0);
    if (!cor){
        return 0;
    }
    *result = cor->primeiro_indice;
    return 1;
}

int inverted_list_primary_search(char result[][TAM_ID_CORREDOR], bool exibir_caminho, int indice, int *indice_final, inverted_list *t) {
	int contador = 0;
    if (exibir_caminho){
        printf(REGS_PERCORRIDOS);
    }
    do{
        if (exibir_caminho){
            printf(" %d", indice);
        }
		if(result != NULL){
        strcpy(result[contador], t->corredor_veiculos_primario_idx[indice].chave_primaria);
        
		}
		if(indice_final != NULL){
    		*indice_final = indice;
		}
		contador++;
        indice = t->corredor_veiculos_primario_idx[indice].proximo_indice;
    } while (indice != -1);
	
	if(exibir_caminho){
		printf("\n");
	}
    return contador;
}

//fui atrás da documentação nessa função para buscar uma melhor compreensão da ideia
void* busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size,
 int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido,
  int retorno_se_nao_encontrado) {

	const char *base = (const char *) base0;
	int lim, cmp, pre = -1, pos = nmemb;
	const void *p, *tp = NULL;
	int x = 0;
	if(exibir_caminho){
		printf(REGS_PERCORRIDOS);
		printf(" ");
	}
	for (lim = nmemb; lim != 0; lim >>= 1) {
		p = base + (lim >> 1) * size;
		x = (((unsigned long)base - (unsigned long)base0)/(unsigned long)size);
		if(exibir_caminho){
			printf("%u ", x + (lim>>1));
		}
		cmp = (*compar)(key, p);
		if (cmp == 0){
			if (exibir_caminho){
				printf("\n");
				exibir_caminho = false;
			}
			tp = p;
			if(posicao_caso_repetido < 0){
				x = x - (lim>>1);
			}else if(posicao_caso_repetido > 0){
				base = (const char *)p + size;
				lim--;
				x++;
			} else{
				break;
			}
		}
		if (cmp > 0) {
			base = (const char *)p + size;
			lim--;
			pre = x;
			x++;
		}else{
			pos = x;
			x = x - (lim>>1);
		}	
	}
	if(tp == NULL){
		if(exibir_caminho){
			printf("\n");
		}
		if(retorno_se_nao_encontrado < 0){
			tp = (const char*) base0 + pre * size;
		}else if(retorno_se_nao_encontrado > 0){
			tp = (const char*) base0 + pos * size;
		}
	}
	
	return (void*)tp;
}

void* busca_binaria(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int retorno_se_nao_encontrado) {
	return busca_binaria_com_reps(key, base0, nmemb, size, compar, exibir_caminho, 0, retorno_se_nao_encontrado);
}

char *strpadright(char *str, char pad, unsigned size){
	for (unsigned i = strlen(str); i < size; ++i)
		str[i] = pad;
	str[size] = '\0';
	return str;
}
char *strupr(char *str){
	for (char *p = str; *p; ++p)
		*p = toupper(*p);
	return str;
}
char *strlower(char *str){
	for (char *p = str; *p; ++p)
		*p = tolower(*p);
	return str;
}
int qsort_string_modelo(const void *a, const void *b){
    return strcmp((char *)a, (char *)b);
}