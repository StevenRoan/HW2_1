import java.io.*;
import java.util.*;

class ColorText{
	
	static List<int[]> topic_color = new ArrayList<int[]>();
	static Map<Integer,String> vocMap = new HashMap<Integer,String>();
	static Random ran = new Random(1);
	
	static void colorTextHeader( BufferedWriter bufw, Integer topic ){
		
		int[] rgb = topic_color.get(topic);
		try{
			bufw.write("\\color[rgb]{");
			bufw.write(rgb[0]/255.0+",");
			bufw.write(rgb[1]/255.0+",");
			bufw.write(rgb[2]/255.0+"}");

		}catch(Exception e){
			e.printStackTrace();
			System.exit(0);
		}
	}

	public static void main(String[] args){
		
		if( args.length < 5){

			System.err.println("Usage: java ColorText [textfile] [vocabulary] [your_output] [num_topics] [color_output] (num_doc_out)");
			System.exit(0);
		}
		
		String text_fname = args[0];
		String voc_fname = args[1];
		try{
			BufferedReader bufr = new BufferedReader(new FileReader(voc_fname));
			String line;
			Integer i = 1;
			while( (line=bufr.readLine()) != null ){
				vocMap.put(i,line);
				i++;
			}
			bufr.close();

		}catch(Exception e){
			e.printStackTrace();
			System.exit(0);
		}
		
		String topic_fname = args[2];
		int num_topics = Integer.valueOf( args[3] );
		String output_fname = args[4];
		int num_doc_out = 10;
		if( args.length >= 6 )
			num_doc_out = Integer.valueOf( args[5] );
		
		//define topic colors
		for(int i=0;i<num_topics;i++){
			int[] rgb = new int[3];
			for(int j=0;j<3;j++)
				rgb[j] = ran.nextInt(256);
			topic_color.add(rgb);
		}


		//read text, topics, output colors
		try{
			BufferedReader bufr_text = new BufferedReader(new FileReader(text_fname));
			BufferedReader bufr_topic = new BufferedReader(new FileReader(topic_fname));

			BufferedWriter bufw = new BufferedWriter(new FileWriter(output_fname));
			bufw.write("\\documentclass{article}\n");
			bufw.write("\\usepackage[dvips]{color}\n");
			bufw.write("\\usepackage{graphicx}\n\n");
			
			bufw.write("\\begin{document}\n\n");
			
			
			String line_text, line_topic;
			String[] tokens_text, tokens_topic;
			Integer doc=0;
			while( (line_text = bufr_text.readLine() ) != null ){
				
				bufw.write("\n\\color[rgb]{0,0,0}\\section{Document"+doc+"}\n");
				
				line_topic = bufr_topic.readLine();
				
				if( line_text.length() < 3 || line_topic.length() < 3 )
					break;

				tokens_text = line_text.split(" ");
				tokens_topic = line_topic.split(" ");
				
				Integer curTopic = Integer.valueOf(tokens_topic[1].split("/")[1])-1;//topic is 1-N, make it 0-N-1
				Integer topic;
				colorTextHeader(bufw,curTopic);
				int cur_key_word=1;
				for(int i=0;i<tokens_text.length;i++){
					
					String token = tokens_text[i].replaceAll("['\"\\.,_`&@*$%^!?():;/\\[\\]\\-0-9]","");
					token = token.toLowerCase();
					if( cur_key_word < tokens_topic.length && 
					token.equals( vocMap.get(Integer.valueOf(tokens_topic[cur_key_word].split("/")[0])) ) ){
						if( !(topic=Integer.valueOf(tokens_topic[cur_key_word].split("/")[1])-1).equals(curTopic) ){//topic is 1-N, make it 0-N-1
							colorTextHeader(bufw,topic);
							curTopic = topic;
						}
						cur_key_word++;
					}
					
					bufw.write(tokens_text[i].replaceAll("['\"\\_&@*$%^/\\[\\]\\{\\}]","")+" ");
				}
				
				bufw.newLine();
				doc++;
				if( doc.equals(num_doc_out) )break;
			}
			
			bufw.write("\n\\end{document}\n");
			bufw.close();
			bufr_text.close();
			bufr_topic.close();

		}catch(Exception e){
			e.printStackTrace();
			System.exit(0);
		}
	}
}
