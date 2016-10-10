#include "vtkwindow.h"
#include "ui_vtkwindow.h"
#include "vtkPolyLine.h"




VtkWindow::VtkWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VtkWindow)
{
    ui->setupUi(this);


    //Traducciones;
    vector<string> tr = {"b","c"};
    vector<string> tr2 = {"d","e"};

    //Test Clase Palabra
    palabra n("a",tr);
    cout << n << endl;
    palabra n2("b",tr2);


vector<string> letras = {"a","g","b","h","i","j","n","o","p","k","l","m","q","r","c","d","e","f"};

for (int co = 0; co<16;co++){
    heap.Insert(palabra(letras[co],tr));
}
    //Heaps -> inserto palabra
//for(int i=0;i<1;i++){
//}

    /*heap.Insert(palabra("a",tr));
    heap.Insert(palabra("2",tr));
    heap.Insert(palabra("3",tr));
    heap.Insert(palabra("4",tr));
    heap.Insert(palabra("5",tr));
    heap.Insert(palabra("6",tr));
    heap.Insert(palabra("8",tr));
    heap.Insert(palabra("7",tr));
    heap.Insert(palabra("9",tr));
    heap.Insert(palabra("10",tr));
    heap.Insert(palabra("11",tr));
    heap.Insert(n);

*/
    //hallar puntos
    heap.puntos(vec);

    //*************TAMAÑO DE PADRES*************
    int tamanio = vec.size();
    cout << "tamanio: " <<tamanio << endl;

    //************TAMAÑO DE HIJOS****************
    int tamanito = vec.at(0).hijos.size();
    cout << "tamanito: " <<tamanito << endl;

    //imprimo puntos
    for(auto it:vec){
        cout<<"1 ";
        it.show() ;
        cout<<endl;
    }

   cout << endl;

   //primer punto"
    cout << vec.at(0).par.x << endl;
    cout << vec.at(0).par.y << endl;
    cout <<"mostrando palabra   "<< vec.at(0).palabra << endl; // Funciona por la sobrecarga si quieres usarlo
    cout <<"qq es esto"<< vec.at(0).palabra.getPalabra() << endl;

        //primer hijo
    cout << vec.at(0).hijos.at(0).x << endl;
    cout << vec.at(0).hijos.at(0).y << endl;
    cout<< "hereeeeeeeeeeeeeeeeeee"<<vec.at(0).hijos.size()<<endl;
    //Codigo VTK


for (int i = 0; i<tamanio;i++){
    double a = ((vec.at(i).par.x)*(1.9))-7;
    double b = (vec.at(i).par.y)*(-1.9)+3;

    //cout <<"a"<<i<<" "<<a<<" b"<<i<<" "<<b<<endl;
    cout<<"parada"<<endl;
    int tamanito2 = vec.at(i).hijos.size();
    cout<<"tamaño"<<tamanito2<<endl;

    for(int j = 0; j<tamanito2;j++){


        cout << vec.at(i).hijos.at(j).x <<" ....  "<< vec.at(i).hijos.at(j).y << endl;

        double c = ((vec.at(i).hijos.at(j).x)*(1.9))-7;
        double d = (vec.at(i).hijos.at(j).y)*(-1.9)+3;

        cout<<a<<" "<<b<<"  "<<c<<"  "<<d<<"askasssssssssssssssssssssssssssssssssssssssssssssssssssss";
        double k = 0.8, t = 0.1;
        double p = c-a;
        double q = d-b;

        double m = a+k*p, n = b+k*q;
        double cx = m+t, cy = n-(t*p)/q;
        double bx = m-t, by = n+(t*p)/q;

        double inicio[3] = {a, b, 0.0};
        double fin[3] = {c, d, 0.0};
        double medio[3]={cx, cy, 0};
        double costa1[3] = {m, n, 0};
        double costa2[3] = {bx, by, 0};

        // Creando los puntos ....
        Points points =Points::New();
        points->InsertNextPoint(inicio);
        points->InsertNextPoint(fin);
        points->InsertNextPoint(medio);
        points->InsertNextPoint(costa1);
        points->InsertNextPoint(fin);
        points->InsertNextPoint(costa2);
        points->InsertNextPoint(medio);



        PolyLine polyLine =PolyLine::New();
        polyLine->GetPointIds()->SetNumberOfIds(7);
        for(unsigned int kl = 0; kl < 7; kl++)
          {
          polyLine->GetPointIds()->SetId(kl,kl);
          }

        // Create a cell array to store the lines in and add the lines to it
        CellArray cells =CellArray::New();
        cells->InsertNextCell(polyLine);

        // Create a polydata to store everything in
        PolyData polyData =PolyData::New();

        // Add the points to the dataset
        polyData->SetPoints(points);

        // Add the lines to the dataset
        polyData->SetLines(cells);

        // Setup actor and mapper
        PolyDataMapper lineasmapper = PolyDataMapper::New();
      #if VTK_MAJOR_VERSION <= 5
        lineasmapper->SetInput(polyData);
      #else
        lineasmapper->SetInputData(polyData);
      #endif

        Actor lineasActor =Actor::New();
        lineasActor->SetMapper(lineasmapper);
        lineasActor->GetProperty()->SetColor(.1,.9,0.0);


        renderer->AddActor(lineasActor);

    }


    SphereSource sphereSource =  SphereSource::New();
     sphereSource->SetCenter(a, b, 0);


    PolyDataMapper sphereMapper = PolyDataMapper::New();
     sphereMapper->SetInputConnection( sphereSource->GetOutputPort() );


    Actor sphereActor = Actor::New();
     sphereActor->SetMapper( sphereMapper );


     sphereActor->GetProperty()->SetColor(.2,.5,0.7);

    //para que sea transparente las bolitas
     sphereActor->GetProperty()->SetOpacity(0.4);

    //PolyDataMapper mapper = PolyDataMapper::New();
     //mapper->SetInputConnection(arrowSource->GetOutputPort());


     TextActor textActor = TextActor::New();
       textActor->SetInput ( "BINOMIAL HEAP" );
       textActor->SetPosition2 ( 8, 20 );
       textActor->GetTextProperty()->SetFontSize ( 15 );
       textActor->GetTextProperty()->SetColor ( .1,.9,0.0);

       //Palabras ...!!!!!

       Follower xLabel = Follower::New();
       VectorText xText = VectorText::New();
       PolyDataMapper xTextMapper = PolyDataMapper::New();;

       std::string str = vec.at(i).palabra.getPalabra();
       const char * c = str.c_str();

       xText->SetText(c);
       xTextMapper->SetInputConnection( xText->GetOutputPort() );
       xLabel->SetMapper( xTextMapper );
       xLabel->SetScale( 0.1 );
       xLabel->SetCamera(renderer->GetActiveCamera());
       //xLabel->SetPosition(((vtkProp3D*)collection->GetItemAsObject( 3 ))->GetCenter()); // XAxisTip
       xLabel->SetPosition(a-0.27,b,0);
       xLabel->PickableOff();

       //Fin palabras !!!

     renderer->AddActor( xLabel );
     renderer->AddActor ( textActor );
     renderer->AddActor( sphereActor );
     renderer->ResetCamera();

}


     renderer->SetBackground(0.0,0.04,0.0);



    //Conexion VTK-QT
    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

    //
}

VtkWindow::~VtkWindow()
{
    delete ui;
}


