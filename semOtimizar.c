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

//Funcao principal
int main() {
    //Recebendo dados do txt

    long int qtde_particulas;
    //Declarando struct particula e alocando memoria.
    struct particula *particulas = (struct particula *) malloc(qtde_particulas * sizeof(struct particula));

    // Calculo e atualizacao dos parametros de cada particula
    calculo_fresultante_particula(particulas, qtde_particulas);

    return 0;
}

//Lendo dados de arquivo de entrada
void ler_dados(){
    float duracao;
    unsigned qtde_intervalos;
    FILE *fp;
    fp = fopen("input.txt", "r");

    if(!fp) {
        printf("Erro na abertura!\n");
        exit(0);
    }
    //Salvando qtde de intervalos e duracao de cada intervalo
    fscanf(fp, "%u %f\n", &qtde_intervalos, &duracao);
    //
    while ((fscanf(arq, "%f %f  %f  %f", &massa, &posx, &posy, &velx, &vely)) != EOF) {

    }

    fclose(fp);
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
        fresultante_total = sqrt(pow(forcas_x,2) + pow(forcas_y,2));
        //Calculando aceleracao
        aceleracao = fresultante_total / particulas[atual_partic].massa;
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
