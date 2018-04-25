#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;


class TratamentoOpenCV
{

private:

    cv::Mat ImagemOriginal;
    cv::Mat ImagemResultado;

    cv::Point PontoInicial = cv::Point(-1,-1); //Para controlar o clique do mouse coloco -1 para os pontos
    cv::Point PontoFinal   = cv::Point(-1,-1); //Para controlar o clique do mouse coloco -1 para os pontos

    string NomeImagemResultado = "resultado.jpg";
    string NomeImagemOriginal;

    void criarImagem(){

     	this->ImagemOriginal = cv::imread( this->NomeImagemOriginal , CV_LOAD_IMAGE_COLOR );

 		if(! this->ImagemOriginal.data )
 		{
 			cout <<  "Imagem nao localizada" << std::endl ;
 		}
 		else{

 			cv::imshow( this->NomeImagemOriginal , this->ImagemOriginal );

 			cv::setMouseCallback( this->NomeImagemOriginal , clickMouse , this );

 			cv::waitKey(0);
 		}
     };

     void criarLinha(){
    	 cv::line( this->ImagemOriginal, this->PontoInicial, this->PontoFinal , cv::Scalar( 110, 220, 0 ),  2, 8 );
     }

     void novaImagem(){

    	cv::imwrite( this->NomeImagemResultado , this->ImagemOriginal );

        this->ImagemResultado = cv::imread( this->NomeImagemResultado , CV_LOAD_IMAGE_COLOR );

        cv::imshow( this->NomeImagemResultado , this->ImagemResultado );
     }

     float calcularEuclidiana()
     {
    	 int dx = this->PontoFinal.x - this->PontoInicial.x;
    	 int dy = this->PontoFinal.y - this->PontoInicial.y;

    	 return cv::sqrt(( pow(dx,2) +pow(dy,2) ));

     }

     static void clickMouse(int event, int x, int y, int flags, void* userdata){

    	 TratamentoOpenCV * trat = reinterpret_cast<TratamentoOpenCV*>(userdata);

    	 if ( event == cv::EVENT_LBUTTONDOWN )
    	 {
    		 //posicao inicial nao tem informacao
    		 if ( trat->PontoInicial.x == -1 and trat->PontoInicial.y == -1  )
    		 {
    			 trat->PontoInicial = cv::Point( x , y ) ;

    			 cout << "Clique inicial - Posicao (" << trat->PontoInicial.x << ", " << trat->PontoInicial.y << ")" << endl;
    		 }
    		 //posicao final nao tem informacao
    		 else if ( trat->PontoFinal.x == -1 and trat->PontoFinal.y == -1 )
    		 {
    			 trat->PontoFinal = cv::Point( x , y ) ;

    			 cout << "Clique final - Posicao (" << trat->PontoFinal.x << ", " << trat->PontoFinal.y << ")" << endl;
    			 cout << "Comprimento em pixel   (" << trat->calcularEuclidiana() << ")" << endl;

    			 trat->criarLinha();

    			 trat->novaImagem();

    		 }
    		 //ja foram passado entao, entao limpo para informar novamente.
    		 else
    		 {
    			 trat->PontoInicial = cv::Point( x , y ); //Passo clique atual
    			 trat->PontoFinal   = cv::Point(-1,-1); //Para controlar o clique do mouse coloco -1 para os pontos

    			 cout << "Clique inicial - Posicao (" << trat->PontoInicial.x << ", " << trat->PontoInicial.y << ")" << endl;

    		 }
    	 }
     }

public:

    TratamentoOpenCV( string imagem ){

        this->NomeImagemOriginal = imagem;

        this->criarImagem();

    };

};


int main( )
{

	TratamentoOpenCV imagem("lena.jpg");

    return 0;
}

