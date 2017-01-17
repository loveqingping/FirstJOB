#include <avro.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#ifdef DEFLATE_CODEC
#define QUICKSTOP_CODEC  "deflate"
#else
#define QUICKSTOP_CODEC  "null"
#endif

avro_schema_t packet_schema;
avro_schema_t msg_body_schema;
#define BODY_MAX_LEN 1024

/* A simple schema for our tutorial */

/*http·¢ËÍÏûÏ¢ÌåµÄschema*/
const char PACKET_SCHEMA[] =
"{\"type\":\"record\",\
        \"name\":\"packet\",\
        \"fields\":[\
{\"name\": \"srcip\", \"type\": \"string\"},\
{\"name\": \"dstip\", \"type\": \"string\"},\
{\"name\": \"content\", \"type\":\"string\"}]}";


    const char MSGBODY_SCHEMA[] =
        "{\"type\":\"record\",\
        \"name\":\"docs\",\
        \"fields\":[\
        {\"name\":\"doc_schema_name\",\"type\":\"string\"},\
    {\"name\":\"sign\",\"type\":\"string\"},\
    {\"name\":\"doc_set\",\"type\":{\"type\":\"array\",\"items\":\"bytes\"}}]}";



    void avro_init_packet_schema(avro_schema_t* packet_schema)
    {
        if (avro_schema_from_json_literal(PACKET_SCHEMA, packet_schema))
        {
            fprintf(stderr, "Unable to parse packet schema:%s\n", avro_strerror());
            exit(EXIT_FAILURE);
        }
    }


    void avro_init_msgbody_schema(avro_schema_t* msgbody_schema)
    {
        if (avro_schema_from_json_literal(MSGBODY_SCHEMA, msgbody_schema))
        {
            fprintf(stderr, "Unable to parse msgbody schema:%s\n", avro_strerror());
            exit(EXIT_FAILURE);
        }
    }

    int avro_add_packet (avro_schema_t packet_schema,
            const int64_t  flow_id, const int64_t  time_stamp,
            const char*    src_ip, const char*    dst_ip, const int      src_port, const int      dst_port,
            const char*    content,
            avro_datum_t  data_array)
    {
        char buf[BODY_MAX_LEN];
        int64_t  datalen =0;
        avro_writer_t    writer; 
        avro_datum_t tmp_datum;

        avro_datum_t packet           = avro_record(packet_schema);

        //avro_datum_t id_datum       = avro_int64(flow_id);
        //avro_datum_t ts_datum       = avro_int64(time_stamp);
        avro_datum_t sip_datum      = avro_string(src_ip);
        avro_datum_t dip_datum      = avro_string(dst_ip);
        //avro_datum_t sport_datum   = avro_int32(src_port);
        //avro_datum_t dport_datum   = avro_int32(dst_port);
        avro_datum_t con_datum     = avro_string(content);


        if (   avro_record_set(packet, "srcip", sip_datum)
                || avro_record_set(packet, "dstip", dip_datum)
                || avro_record_set(packet, "content", con_datum))
        {   
            fprintf(stderr, " error message: %s\n", avro_strerror());
            return 1;

        }

        writer = avro_writer_memory(buf, BODY_MAX_LEN);
        avro_write_data(writer, packet_schema, packet);
        datalen    = avro_size_data(writer, packet_schema, packet);
        tmp_datum  = avro_bytes(buf, datalen);
        avro_array_append_datum(data_array, tmp_datum);

       avro_datum_decref(packet);
     //avro_datum_decref(id_datum);
    // avro_datum_decref(ts_datum);
       avro_datum_decref(sip_datum);
       avro_datum_decref(dip_datum);
     //avro_datum_decref(sport_datum);
     //avro_datum_decref(dport_datum);
       avro_datum_decref(con_datum);
       avro_datum_decref (tmp_datum);

       avro_writer_free(writer);

        return 0;
    }
    int  avro_add_msgbody (avro_schema_t  msgbody_schema,const char * name, const char * sign,avro_datum_t  data_array, avro_datum_t  msg_body)
    {
        avro_datum_t name_datum = avro_string (name);
        avro_datum_t sign_datum  = avro_string (sign);

        if (avro_record_set  (msg_body, "doc_schema_name", name_datum)
                ||  avro_record_set  (msg_body, "sign", sign_datum)
                ||avro_record_set  (msg_body, "doc_set", data_array) )
        {
            fprintf(stderr, " error message: %s\n", avro_strerror());
            return 1;
        }

        avro_datum_decref (name_datum);
        avro_datum_decref (sign_datum);

        return 0;
    }

    int main(void)
    {
        char buf[10240];

        avro_init_packet_schema (&packet_schema);
        avro_init_msgbody_schema (&msg_body_schema);

        avro_schema_t array_schema = avro_schema_array(avro_schema_bytes());
        avro_datum_t    data_array  = avro_datum_from_schema(array_schema);
        int i=0;
        for(i=0;i<2;i++){
            avro_add_packet (packet_schema,1, 2,"3132","4",5,6,"7",data_array);
        }
        avro_datum_t  body_record  = avro_record ( msg_body_schema) ;
        avro_add_msgbody (msg_body_schema, "packet",  "this is sign",data_array , body_record);

        avro_writer_t writer = avro_writer_memory(buf,  BODY_MAX_LEN);
        avro_write_data(writer, msg_body_schema, body_record);
        int64_t data_len  = avro_size_data(writer,msg_body_schema, body_record);

        struct curl_slist *plist = NULL;
        plist = curl_slist_append(NULL, "Expect:100-Continue");
        curl_slist_append(plist, "Content-Type: binary/octet-stream");
        curl_slist_append(plist, "Transfer-Encoding:chunked");
        curl_slist_append(plist,"Connection: Keep-Alive");

        CURL * easy_handle = curl_easy_init();
        curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, plist);
        curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDS, buf);
        curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDSIZE, data_len);

        curl_easy_setopt(easy_handle, CURLOPT_URL, "http://192.168.11.95:8015/dataload/");
        CURLcode res = curl_easy_perform(easy_handle);
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
        }

        avro_writer_free(writer);
        avro_schema_decref (array_schema);
        return 0;
    }


