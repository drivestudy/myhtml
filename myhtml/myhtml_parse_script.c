//
//  myhtml_parse_script.c
//  myhtml
//
//  Created by Alexander Borisov on 17.10.15.
//  Copyright © 2015 Alexander Borisov. All rights reserved.
//

#include "myhtml_parse_script.h"


size_t myhtml_parse_state_script_data(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    
    while (html_offset < html_size)
    {
        if(html[html_offset] == '<')
        {
            myhtml_parse_inc_html_offset(html_offset, html_size);
            
            // skip state: script_data_less_than_sign, script_data_escate_start and script_data_escate_start_dash
            if(html[html_offset] == '/')
            {
                myhtml_parse_inc_html_offset(html_offset, html_size);
                
                if(myhtml_ascii_char_cmp(html[html_offset]))
                {
                    mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_END_TAG_NAME;
                    break;
                }
            }
            else if(html[html_offset] == '!')
            {
                myhtml_parse_inc_html_offset(html_offset, html_size);
                
                size_t next_offset = html_offset + 1;
                
                if(next_offset < html_size)
                {
                    if(html[html_offset] == '-' && html[next_offset] == '-')
                    {
                        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED_DASH_DASH;
                        
                        html_offset = next_offset + 1;
                        break;
                    }
                }
            }
        }
        
        html_offset++;
    }
    
    return html_offset;
}

// see myhtml_parse_state_script_data
size_t myhtml_parse_state_script_data_less_than_sign(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    return html_offset;
}

// see myhtml_parse_state_script_data
size_t myhtml_parse_state_script_data_escape_start(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    return html_offset;
}

// see myhtml_parse_state_script_data
size_t myhtml_parse_state_script_data_escape_start_dash(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    return html_offset;
}

// see myhtml_parse_state_script_data
size_t myhtml_parse_state_script_data_end_tag_open(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    
    if(myhtml_ascii_char_cmp(html[html_offset])) {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_END_TAG_NAME;
    }
    else {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA;
        html_offset++;
    }
    
    return html_offset;
}

size_t myhtml_parse_state_script_data_end_tag_name(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    myhtml_t* myhtml = tree->myhtml;
    
    size_t offset_cache = html_offset;
    
    while(html_offset < html_size)
    {
        if(myhtml_whithspace(html[html_offset], ==, ||))
        {
            if(strncasecmp(&html[offset_cache], "script", 6) == 0)
            {
                myhtml_parse_queue_create_text_node_if_need(tree, html, offset_cache - 2);
                
                mh_tree_token_current(tag_begin) = offset_cache - 2;
                mh_tree_token_current(tagname_begin) = offset_cache;
                mh_tree_token_current(tagname_length) = 6;
                mh_tree_token_current(tag_ctx_idx) = MyTAGS_TAG_SCRIPT;
                mh_tree_token_current(type) = MyHTML_TOKEN_TYPE_CLOSE;
                
                mh_state_set(tree) = MyHTML_PARSE_STATE_BEFORE_ATTRIBUTE_NAME;
            }
            else {
                mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA;
            }
            
            html_offset++;
            break;
        }
        else if(html[html_offset] == '/')
        {
            if(strncasecmp(&html[offset_cache], "script", 6) == 0)
            {
                myhtml_parse_queue_create_text_node_if_need(tree, html, offset_cache - 2);
                
                mh_tree_token_current(tag_begin) = offset_cache - 2;
                mh_tree_token_current(tagname_begin) = offset_cache;
                mh_tree_token_current(tagname_length) = 6;
                mh_tree_token_current(tag_ctx_idx) = MyTAGS_TAG_SCRIPT;
                mh_tree_token_current(type) = MyHTML_TOKEN_TYPE_CLOSE|MyHTML_TOKEN_TYPE_CLOSE_SELF;
                
                mh_state_set(tree) = MyHTML_PARSE_STATE_BEFORE_ATTRIBUTE_NAME;
            }
            else {
                mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA;
            }
            
            html_offset++;
            break;
        }
        else if(html[html_offset] == '>')
        {
            if(strncasecmp(&html[offset_cache], "script", 6) == 0)
            {
                myhtml_parse_queue_create_text_node_if_need(tree, html, offset_cache - 2);
                
                mh_tree_token_current(tag_begin) = offset_cache - 2;
                mh_tree_token_current(tag_length) = (html_offset - mh_tree_token_current(tag_begin)) + 1;
                mh_tree_token_current(tagname_begin) = offset_cache;
                mh_tree_token_current(tagname_length) = 6;
                mh_tree_token_current(tag_ctx_idx) = MyTAGS_TAG_SCRIPT;
                mh_tree_token_current(type) = MyHTML_TOKEN_TYPE_CLOSE;
                
                html_offset++;
                mh_queue_add(tree, html, mh_queue_current(), html_offset);
                
                mh_state_set(tree) = MyHTML_PARSE_STATE_DATA;
            }
            else {
                mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA;
                html_offset++;
            }
            
            break;
        }
        else if(myhtml_ascii_char_unless_cmp(html[html_offset]))
        {
            mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA;
            break;
        }
        
        html_offset++;
    }
    
    return html_offset;
}

size_t myhtml_parse_state_script_data_escaped_dash_dash(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    
    if(html[html_offset] == '-') {
        html_offset++;
        return html_offset;
    }
    
    if(html[html_offset] == '<') {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN;
    }
    else if(html[html_offset] == '>') {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA;
    }
    else {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED;
    }
    
    html_offset++;
    
    return html_offset;
}

size_t myhtml_parse_state_script_data_escaped_less_than_sign(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    
    if(html[html_offset] == '/') {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED_END_TAG_OPEN;
        html_offset++;
    }
    else if(myhtml_ascii_char_cmp(html[html_offset])) {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_DOUBLE_ESCAPE_START;
    }
    else {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED;
    }
    
    return html_offset;
}

size_t myhtml_parse_state_script_data_escaped_end_tag_open(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    
    if(myhtml_ascii_char_cmp(html[html_offset])) {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED_END_TAG_NAME;
    }
    else {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED;
    }
    
    return html_offset;
}

size_t myhtml_parse_state_script_data_escaped_end_tag_name(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    myhtml_t* myhtml = tree->myhtml;
    
    size_t offset_cache = html_offset;
    
    while(html_offset < html_size)
    {
        if(myhtml_whithspace(html[html_offset], ==, ||))
        {
            if(strncasecmp(&html[offset_cache], "script", 6) == 0)
            {
                myhtml_parse_queue_create_text_node_if_need(tree, html, offset_cache - 2);
                
                mh_tree_token_current(tag_begin) = offset_cache - 2;
                mh_tree_token_current(tagname_begin) = offset_cache;
                mh_tree_token_current(tagname_length) = 6;
                mh_tree_token_current(tag_ctx_idx) = MyTAGS_TAG_SCRIPT;
                mh_tree_token_current(type) = MyHTML_TOKEN_TYPE_CLOSE;
                
                mh_state_set(tree) = MyHTML_PARSE_STATE_BEFORE_ATTRIBUTE_NAME;
            }
            else {
                mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED;
            }
            
            html_offset++;
            break;
        }
        else if(html[html_offset] == '/')
        {
            if(strncasecmp(&html[offset_cache], "script", 6) == 0)
            {
                myhtml_parse_queue_create_text_node_if_need(tree, html, offset_cache - 2);
                
                mh_tree_token_current(tag_begin) = offset_cache - 2;
                mh_tree_token_current(tagname_begin) = offset_cache;
                mh_tree_token_current(tagname_length) = 6;
                mh_tree_token_current(tag_ctx_idx) = MyTAGS_TAG_SCRIPT;
                mh_tree_token_current(type) = MyHTML_TOKEN_TYPE_CLOSE|MyHTML_TOKEN_TYPE_CLOSE_SELF;
                
                mh_state_set(tree) = MyHTML_PARSE_STATE_BEFORE_ATTRIBUTE_NAME;
            }
            else {
                mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED;
            }
            
            html_offset++;
            break;
        }
        else if(html[html_offset] == '>')
        {
            if(strncasecmp(&html[offset_cache], "script", 6) == 0)
            {
                myhtml_parse_queue_create_text_node_if_need(tree, html, offset_cache - 2);
                
                mh_tree_token_current(tag_begin) = offset_cache - 2;
                mh_tree_token_current(tagname_begin) = offset_cache;
                mh_tree_token_current(tagname_length) = 6;
                mh_tree_token_current(tag_ctx_idx) = MyTAGS_TAG_SCRIPT;
                mh_tree_token_current(type) = MyHTML_TOKEN_TYPE_CLOSE;
                
                mh_state_set(tree) = MyHTML_PARSE_STATE_DATA;
                
                html_offset++;
                mh_queue_add(tree, html, mh_queue_current(), html_offset);
            }
            else {
                mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED;
                html_offset++;
            }
            
            break;
        }
        else if(myhtml_ascii_char_unless_cmp(html[html_offset]))
        {
            mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED;
            break;
        }
        
        html_offset++;
    }
    
    return html_offset;
}

size_t myhtml_parse_state_script_data_escaped(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    
    while(html_offset < html_size)
    {
        if(html[html_offset] == '-')
        {
            mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED_DASH;
            html_offset++;
            break;
        }
        else if(html[html_offset] == '<')
        {
            mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN;
            html_offset++;
            break;
        }
        
        html_offset++;
    }
    
    return html_offset;
}

size_t myhtml_parse_state_script_data_escaped_dash(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    
    if(html[html_offset] == '-') {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED_DASH_DASH;
        html_offset++;
    }
    else if(html[html_offset] == '<') {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN;
    }
    else {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED;
        html_offset++;
    }
    
    return html_offset;
}

size_t myhtml_parse_state_script_data_double_escape_start(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    
    size_t offset_cache = html_offset;
    
    while(html_offset < html_size)
    {
        if(myhtml_whithspace(html[html_offset], ==, ||) || html[html_offset] == '/' || html[html_offset] == '>')
        {
            if((html_offset - offset_cache) > 5 && strncasecmp(&html[offset_cache], "script", 6) == 0) {
                mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_DOUBLE_ESCAPED;
            }
            else {
                mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED;
            }
            
            html_offset++;
            break;
        }
        else if(myhtml_ascii_char_unless_cmp(html[html_offset]))
        {
            mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED;
            break;
        }
        
        html_offset++;
    }
    
    return html_offset;
}

size_t myhtml_parse_state_script_data_double_escaped(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    
    while(html_offset < html_size)
    {
        if(html[html_offset] == '-')
        {
            mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_DOUBLE_ESCAPED_DASH;
            html_offset++;
            break;
        }
        else if(html[html_offset] == '<')
        {
            mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN;
            html_offset++;
            break;
        }
        
        html_offset++;
    }
    
    return html_offset;
}

size_t myhtml_parse_state_script_data_double_escaped_dash(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    
    if(html[html_offset] == '-')
    {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH;
    }
    else if(html[html_offset] == '<')
    {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN;
    }
    else {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_DOUBLE_ESCAPED;
    }
    
    html_offset++;
    
    return html_offset;
}

size_t myhtml_parse_state_script_data_double_escaped_dash_dash(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    
    if(html[html_offset] == '-') {
        html_offset++;
        return html_offset;
    }
    
    if(html[html_offset] == '<')
    {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN;
    }
    else if(html[html_offset] == '>')
    {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA;
    }
    else {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_DOUBLE_ESCAPED;
    }
    
    html_offset++;
    
    return html_offset;
}

size_t myhtml_parse_state_script_data_double_escaped_less_than_sign(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    
    if(html[html_offset] == '/') {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_DOUBLE_ESCAPE_END;
        html_offset++;
    }
    else {
        mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_DOUBLE_ESCAPED;
    }
    
    return html_offset;
}

size_t myhtml_parse_state_script_data_double_escape_end(myhtml_tree_t* tree, const char* html, size_t html_offset, size_t html_size)
{
    //myhtml_t* myhtml = tree->myhtml;
    
    size_t offset_cache = html_offset;
    
    while(html_offset < html_size)
    {
        if(myhtml_whithspace(html[html_offset], ==, ||) || html[html_offset] == '/' || html[html_offset] == '>')
        {
            if((html_offset - offset_cache) > 5 && strncasecmp(&html[offset_cache], "script", 6) == 0) {
                mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_ESCAPED;
            }
            else {
                mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_DOUBLE_ESCAPED;
            }
            
            html_offset++;
            break;
        }
        else if(myhtml_ascii_char_unless_cmp(html[html_offset]))
        {
            mh_state_set(tree) = MyHTML_PARSE_STATE_SCRIPT_DATA_DOUBLE_ESCAPED;
            break;
        }
        
        html_offset++;
    }
    
    return html_offset;
}


