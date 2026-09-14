//
// Created by Mateusz M on 24/06/2026.
//

#ifndef JSON_PARSER_GRAPHBUILDER_HPP
#define JSON_PARSER_GRAPHBUILDER_HPP

#include "../include/JsonParserLib/JSON_Parser.hpp"
#include <iostream>
#include <list>
#include <set>
#include <stack>
#include "../../Algosy2Grafy/include/HelperFunctions.hpp"
#include "../../Algosy2Grafy/include/Edge.hpp"

enum retrieve_mode {EDGE, NODE};
template <typename T>
class GraphBuilder {

    std::list< std::string > instructions_list;
    json::JSON_Node* root_node;
    std::list<json::JSON_Node*> node_stack;

public:
    std::set<T> nodes_result;
    std::set<Edge<T>*> edge_result;

    explicit GraphBuilder( const json::JSON_Parser& tree ): root_node( tree() ) {}
    ~GraphBuilder() {
        for (auto e : edge_result) delete e;
        node_stack.clear();
    }
    void addInstruction( const std::string& instr ) {
        this->instructions_list.push_back( instr );
    }
    void retrieve( retrieve_mode mode, bool weighed = false) {
        auto current_node = root_node;
        nodes_result.clear();

        node_stack.clear();
        node_stack.push_front(root_node);
        // instructions_list.clear();
        bool found_source = false;
        bool found_target = false;
        T source, target;
        json::JSON_Node* previous_node = nullptr;

        while ( !this->instructions_list.empty() ) {

            DEBUG_LOG(std::format("\n@CURRENT NODE val={} type={}", current_node->node_value.as_str, json::type_map[current_node->node_value.type]))
            DEBUG_LOG(std::format("@INSTRUCTIONS LEFT: {}", this->instructions_list.size()))
            DEBUG_LOG(std::format("@INSTRUCTIONS QUEUE: {}", str(this->instructions_list)))
            DEBUG_LOG( "#Current node: " << current_node )
            DEBUG_LOG( "#Previous node: " << previous_node )
                        std::cout << "#Current node stack: ";
            for (auto n : node_stack) {
                std::cout << n << ", ";
            }
            std::cout << std::endl;


            // Retrieve first instruction
            auto instruction = this->instructions_list.front();
            this->instructions_list.pop_front();


            if ( instruction[0] == '@') {
                if ( instruction == "@forelements" ) {
                    std::list<std::string> new_instructions;

                    // Find the loop closed
                    // TODO implement loop depth
                    auto endfor_it = std::find_if(
                        this->instructions_list.begin(),
                        this->instructions_list.end(),
                        []( const std::string& inst) {
                            return inst == "@endfor";
                        }
                    );
                    // Error if no loop closing found
                    if ( endfor_it == this->instructions_list.end() ) {
                        throw std::runtime_error("Missing @endfor instruction");
                    }

                    // auto head = std::ranges::subrange(this->instructions_list.begin(), endfor_it);
                    // DEBUG_LOG( str(head) );
                    // auto tail = std::ranges::subrange(endfor_it, this->instructions_list.end());
                    // DEBUG_LOG( str(tail) )


                    for ( auto& entry: current_node->children ) {
                        DEBUG_LOG( current_node->children.size() )
                        // DEBUG_LOG( "key: " << get<int>(entry.first) << "\n" )

                        // DEBUG_LOG("meow1")
                        // new_instructions.insert(
                        //     new_instructions.begin(),
                        //     this->instructions_list.begin(),
                        //     endfor_it
                        //     );
                        // DEBUG_LOG("meow2")
                        // new_instructions.push_front("@from_stack");
                        // DEBUG_LOG("meow3")
                        // DEBUG_LOG((void*)child);
                        // node_stack.push_front( child);
                        // DEBUG_LOG("meow4")
                        // DEBUG_LOG( current_node->children.size() )
                    }
                    DEBUG_LOG("meow5")
                    new_instructions.insert( new_instructions.end(), std::next(endfor_it), this->instructions_list.end() );
                    this->instructions_list = std::move(new_instructions);
                    // DEBUG_LOG( lstr(this->instructions_list) )
                }

                else if ( instruction == "@keys" ) {
                    for (const auto key: current_node->children | std::views::keys) {
                        this->nodes_result.insert( get<std::string>(key) ); // string cus keys in dicts are only string
                    }
                }


                else if ( instruction == "@value" ) {

                    if ( mode == EDGE ) {
                        if (found_source == false and found_target == false) {
                            source = get<T>(current_node->node_value.value);
                            found_source = true;
                        }
                        else if ( found_target == false ) {
                            target = get<T>(current_node->node_value.value);
                            found_target = true;
                            found_source = false;
                            // DEBUG_LOG(std::format("# EDGE {}->{}", source, target));
                            if (!weighed) this->edge_result.insert( new Edge<T>(source, target) );
                        }
                        else {
                            // DEBUG_LOG( current_node->node_value.as_str )
                            if (weighed) {
                                this->edge_result.insert( new Edge<T>(source, target, get<float>(current_node->node_value.value)) );
                                found_target = false;
                            }
                        }
                    }
                    else {
                        this->nodes_result.insert( get<T>(current_node->node_value.value) );
                    }
                    current_node = previous_node;

                }

                else if ( instruction == "@root") {
                    current_node = root_node;
                }

                else if ( instruction == "@from_stack") {
                    current_node = node_stack.front();
                    node_stack.pop_front();
                }

            }
            else {
                previous_node = current_node;
                auto next_node = current_node->operator[]( instruction.c_str() );
                current_node = &next_node;
            }
        }
    }
};


#endif //JSON_PARSER_GRAPHBUILDER_HPP
