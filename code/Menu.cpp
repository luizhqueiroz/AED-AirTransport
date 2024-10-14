#include "Menu.h"

Menu::Menu(DataSet dataset) : dataset{dataset}
{
    principal();
}

void Menu::menu()
{
    cout << "\n===================================================== \n";
    cout << " \t\tMENU \t \n ";
    cout << "===================================================== \n";
    cout << " 1. Lista dos Países\n";
    cout << " 2. Lista dos Aeroportos\n";
    cout << " 3. Lista das Companhias Aéreas\n";
    cout << " 4. Trajetos entre Dois Locais\n";
    cout << " 5. Distância entre Aeroportos\n";
    cout << " 6. Informações sobre um Aeroporto\n";
    cout << " 7. Estatísticas\n";
    cout << " 8. Encerrar\n\n";
}

string Menu::submenu(string txt)
{
    string str = "";

    while ( 1 )
    {
        cout << "Escolher um " << txt << ": ";
        getline(cin, str);
        cout << endl;

        if ( txt == "pais")
        {
            if ( dataset.getCountry(str) != nullptr )
                return str;
            else
                cout << "País " << str << " Desconhecido\n";
        }
        else if ( txt == "aeroporto")
        {
            if ( dataset.getAirport(str) != nullptr )
                return str;
            else
                cout << "Aeroporto " << str << " Desconhecido\n";
        }
        else if ( txt == "companhia" )
        {
            if ( dataset.getAirline(str) != nullptr )
                return str;
            else
                cout << "Companhia Aérea " << str << " Desconhecida\n";
        }
        else if ( txt == "cidade" )
        {
            if ( dataset.getCity(str) != nullptr )
                return str;
            else
                cout << "Cidade " << str << " Desconhecida\n";
        }
    }

    return "";
}

void Menu::submenu4_text()
{
    cout << endl;
    cout << " 1. Trajeto entre Aeroportos\n";
    cout << " 2. Trajeto entre Cidades\n";
}

char Menu::submenu4()
{
    char key;
    string str;

    submenu4_text();

    do
    {
        cout << "\nEscolher (1-2): ";

        getline(cin, str);
        key = str[0];
    }
    while ( key != '1' && key != '2' );

    return key;
}

void Menu::submenu3_text(int opt)
{
    cout << endl;
    cout << " 1. Estatísticas Globais da Rede\n";
    cout << " 2. Estatísticas de um País\n";

    if ( opt == 1 )
        cout << " 3. Estatísticas de uma Companhia Aérea\n\n";
}

char Menu::submenu3(int opt,string* info)
{
    char key;
    string str;

    submenu3_text(opt);

    do
    {
        if ( opt == 1 )
            cout << "\nEscolher (1-3): ";
        else
            cout << "\nEscolher (1-2): ";

        getline(cin, str);
        key = str[0];
    }
    while ( !( key == '1' || key == '2' || (key == '3' && opt == 1)) );

    return key;
}

void Menu::submenu2_text()
{
    cout << endl;
    cout << " 1. Número de Aeroportos\n";
    cout << " 2. Número de Voos\n";
    cout << " 3. Número de Companhias Aéreas\n";
    cout << " 4. Top-K de Aeroportos com mais Voos\n";
    cout << " 5. Top-K de Aeroportos com mais Companhias Aéreas\n";
    cout << " 6. Retornar ao Menu Principal\n\n";
}

void Menu::submenu2()
{
    bool quit = false;
    char key, type;
    string str, info;

    submenu2_text();

    do
    {
        cout << "Escolher (1-6): ";
        getline(cin, str);
        key = str[0];

        switch ( key )
        {
            case '1':
                type = submenu3(1, &info);

                if (type == '2')
                    info = submenu("pais");

                else if (type == '3')
                    info = submenu("companhia");

                dataset.numAirports(type, info);
                break;

            case '2':
                type = submenu3(1,&info);

                if ( type == '2')
                    info = submenu("pais");
                else if ( type == '3')
                    info = submenu("companhia");

                dataset.numFlights(type,info);
                break;

            case '3':
                type = submenu3(0,&info);

                if ( type == '2')
                    info = submenu("pais");

                dataset.numAirlines(type,info);
                break;

            case '4':
                type = submenu3(0,&info);

                if ( type == '2')
                    info = submenu("pais");

                dataset.topKvoos(type,info);
                break;

            case '5':
                type = submenu3(0,&info);

                if ( type == '2')
                    info = submenu("pais");

                dataset.topKairlines(type,info);
                break;

            case '6':
                quit = true;
                break;
        }

        if (!quit)
            submenu2_text();

    }
    while (!quit);
}

void Menu::principal()
{
    string str,pais,source,target;
    bool quit = false;
    char key,type;

    menu();

    do
    {
        cout << "Escolher (1-8): ";
        getline(cin, str);
        key = str[0];

        switch (key)
        {
            case '1':
                dataset.printCountries();
                break;

            case '2':
                pais = submenu("pais");
                dataset.printAirports(pais);
                break;

            case '3':
                pais = submenu("pais");
                dataset.printAirlines(pais);
                break;

            case '4':
                type = submenu4();

                if ( type == '1' )
                {
                    do
                    {
                        source = submenu("aeroporto");
                        target = submenu("aeroporto");
                    }
                    while ( !dataset.testAirports(source,target) );

                    dataset.getGraph()->print_paths_airports(source,target);
                }
                else if ( type == '2' )
                {
                    do
                    {
                        source = submenu("cidade");
                        target = submenu("cidade");

                        if ( source == target )
                            cout << "As Cidades devem ser diferentes\n";
                    }
                    while ( source == target );

                    dataset.getGraph()->print_paths_cities(source,target);
                }

                break;

            case '5':
                do
                {
                    source = submenu("aeroporto");
                    target = submenu("aeroporto");
                }
                while ( !dataset.testAirports(source,target) );

                dataset.printDistance(source,target);
                break;

            case '6':
                source = submenu("aeroporto");
                dataset.getGraph()->printFlights(source);
                break;

            case '7':
                submenu2();
                break;

            case '8':
                quit = true;
        }

        if (!quit)
            menu();
    } while (!quit);
}
