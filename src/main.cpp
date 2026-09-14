//
// Created by Mateusz M on 08/06/2026.
//

#include "../../JSON_Parser/include/JsonParserLib/JSON_Parser.hpp"
#include "../include/GraphLib/ListGraph.hpp"
#include <iostream>



using namespace json;

template <typename T>
ListGraph<T> buildGraph1( const std::string& file_name) {

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

/*
template <typename T>
ListGraph<T> buildGraph2( const std::string& file_name) {

    // Initialize the parser
    auto parser = JSON_Parser(true);
    parser.setDirectory("json");
    parser.importFile( file_name );
    parser.parse();

    bool directed = parser["graph"]["directed"].as<bool>();
    auto result = ListGraph<T>(directed);

    // Add nodes
    const auto nodes = std::set<std::string>();
    for ( auto entry : parser["graph"]["content"].keys() ) {
        auto str_node = get<std::string>(entry);
        // nodes.insert( str_node );
        result.add_node( str_node );
    }

    for ( auto source : parser["graph"]["content"].keys() ) {
        for ( auto target_entry: parser["graph"]["content"][get<std::string>(source).c_str()].keys() ) {
            auto str_target = get<std::string>(target_entry);
            result.add_edge(get<std::string>(source), str_target, parser["graph"]["content"][get<std::string>(source).c_str()][str_target.c_str()].as<float>());
        }
    }

    return result;
}
*/

int main() {
    buildGraph1<std::string>( "Graph.json" ).display();
    return 0;
}
