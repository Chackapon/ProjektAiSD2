//
// Created by Mateusz M on 08/06/2026.
//

#include "../../JSON_Parser/include/JsonParserLib/JSON_Parser.hpp"
#include "../include/GraphLib/ListGraph.hpp"
#include <iostream>



using namespace json;

template <typename T>
ListGraph<T> buildGraph( const std::string& file_name) {

    // Initialize the parser
    auto parser = JSON_Parser(true);
    parser.setDirectory("json");
    parser.importFile( file_name );
    parser.parse();

    bool directed = parser["directed"].as<bool>();
    auto result = ListGraph<T>(directed);

    // Add nodes
    const auto nodes_amount = parser["nodes"].keys().size();
    for ( int i = 0; i < static_cast<int>(nodes_amount);  ++i ) {
        auto node_id = parser["nodes"][i]["id"].as< std::string >();
        // DEBUG_LOG(node_id)
        result.add_node(node_id);
    }

    // Add edges
    const auto edges_amount = parser["edges"].keys().size();
    for ( int i = 0; i < static_cast<int>(edges_amount);  ++i ) {
        auto source_id = parser["edges"][i]["source"].as< std::string >();
        auto target_id = parser["edges"][i]["target"].as< std::string >();
        auto weight = parser["edges"][i]["weight"].as< float >();
        result.add_edge( source_id, target_id, weight );
    }
    return result;
}


int main() {
    buildGraph<std::string>( "Graph.json" ).display();
    return 0;
}
