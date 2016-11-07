#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define G 6.67

/*Observações e Tarefas
    - Não adicionamos o valor de 10⁻¹¹ as contas onde G está envolvido.
    - Pensar em uma forma de salvar essa constante G de modo que não ultrapasse o tamanho de um float.
    - A velocidade será em algum momento maior que a capacidade de um float?
    - Estou usando long int em 'qtde_particulas', 'atual' e 'outra' pois eles poderão
      receber valores que ultrapassem os 32767 do int.
*/


struct particula{
    float massa;
    float posicao_x;
    float posicao_y;
    float velocidade_x;
    float velocidade_y;
};

//Declaracao de funcoes
void calculo_fresultante_particula(struct particula *particulas, long int qtde_particulas);
void calculo_forca_bruta(struct particula *particulas, float *forcas_x, float *forcas_y, long int atual, long int outra);
struct particula* ler_dados(long int *qtde_particulas);

//Funcao principal
int main() {
    //Recebendo dados do txt

    long int qtde_particulas = 0;
    //Declarando struct particula.
    struct particula *particulas;

    //Lendo dados do arquivo de entrada e atualizando struct particula.
    particulas = ler_dados(&qtde_particulas);

    //printf("%f %f %f\n", particulas[1].massa, particulas[1].posicao_x, particulas[1].posicao_y);
    //printf("Quantidade particulas: %li\n", qtde_particulas);

    // Calculo e atualizacao dos parametros de cada particula
    calculo_fresultante_particula(particulas, qtde_particulas);

    return 0;
}

//Lendo dados de arquivo de entrada
struct particula* ler_dados(long int *qtde_particulas){
    float duracao;
    float massa, posx, posy, velx, vely;
    unsigned qtde_intervalos;
    FILE *fp;

    fp = fopen("input.txt", "r");
    if(!fp) {
        printf("Erro na abertura!\n");
        exit(0);
    }

    struct particula *particulas = (struct particula *) malloc(sizeof(struct particula));

    //Salvando qtde de intervalos e duracao de cada intervalo
    fscanf(fp, "%u %f\n", &qtde_intervalos, &duracao);
    //
    while ((fscanf(fp, "%f  %f  %f  %f  %f", &massa, &posx, &posy, &velx, &vely)) != EOF) {
        (*qtde_particulas)++;
        //Realoca o tamanho do vetor para quantidade atual de particulas
        particulas = (struct particula *) realloc(particulas, (*qtde_particulas)* sizeof(struct particula));
        //Preenche a struct com os valores do arquivo de entrada.
        particulas[(*qtde_particulas)-1].massa = massa;
        particulas[(*qtde_particulas)-1].posicao_x = posx;
        particulas[(*qtde_particulas)-1].posicao_y = posy;
        particulas[(*qtde_particulas)-1].velocidade_x = velx;
        particulas[(*qtde_particulas)-1].velocidade_y = vely;
    }

    fclose(fp);
    return particulas;
}

/* Forca gravitacional de todas as particulas sobre uma unica particula e
    atualizacao dos paramentros.*/
void calculo_fresultante_particula(struct particula *particulas, long int qtde_particulas) {

    float forcas_x, forcas_y, fresultante_total, aceleracao;
    long int atual_partic, outra_partic;
    //Chamando funcoes
    for (atual_partic = 0; atual_partic < qtde_particulas; atual_partic++) {

        forcas_x = 0.0, forcas_y = 0.0, fresultante_total = 0.0, aceleracao = 0.0;

        for (outra_partic = 0; outra_partic < qtde_particulas; outra_partic++) {
            if(outra_partic != atual_partic)
                calculo_forca_bruta(particulas, &forcas_x, &forcas_y, atual_partic, outra_partic);
        }

        // Calculando forca resultante total na particula
        fresultante_total = sqrt( ( pow (forcas_x,2) ) + ( pow(forcas_y,2) ) );
        //Calculando aceleracao
        aceleracao = fresultante_total / particulas[atual_partic].massa;

        printf("%liª Partícula: F. resultante = %f, aceleracao = %f\n", atual_partic+1, fresultante_total, aceleracao);
        //Calcular velocidades em x e y, e atualizar.

        //Calcular nova posicao_x e posicao_y
    }

    return;
}

// Força gravitacional de uma partícula sobre outra unica particula
void calculo_forca_bruta(struct particula *particulas, float *forcas_x, float *forcas_y, long int atual, long int outra){
    float fresultante;
    float distancia, distancia_x, distancia_y;

    //Calculando distancia entre dois pontos
    distancia_x = particulas[outra].posicao_x - particulas[atual].posicao_x;
    distancia_y = particulas[outra].posicao_y - particulas[atual].posicao_y;
    distancia = sqrt(pow(distancia_x, 2) + pow(distancia_y, 2));

    fresultante = (G * particulas[atual].massa * particulas[outra].massa)/distancia;
    //Calculo da forca resultante em X
    *forcas_x +=  fresultante * cos(distancia_x / distancia);
    //Calculo da forca resultante em Y
    *forcas_y += fresultante * cos(distancia_y / distancia);

    return;
}
