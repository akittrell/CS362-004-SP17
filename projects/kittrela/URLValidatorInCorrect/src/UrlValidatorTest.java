/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
 UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //VALID URLS
	   System.out.println("-------| BELOW SHOULD RETURN TRUE |--------");
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   
	   //capitals
	   System.out.println(urlVal.isValid("http://www.Google.com"));
	   System.out.println(urlVal.isValid("http://www.gOogle.com"));
	   System.out.println(urlVal.isValid("http://www.goOgle.com"));
	   System.out.println(urlVal.isValid("http://www.gooGle.com"));
	   System.out.println(urlVal.isValid("http://www.googLe.com"));
	   System.out.println(urlVal.isValid("http://www.googlE.com"));
	   
	   //https as scheme
	   System.out.println(urlVal.isValid("https://www.amazon.com"));
	   
	   //ftp as scheme
	   System.out.println(urlVal.isValid("ftp://www.amazon.com"));
	  
	   //Properly formated scheme
	   System.out.println(urlVal.isValid("totallyVal://www.google.com"));
	   
	   // .org, .edu, .gov tested
	   System.out.println(urlVal.isValid("http://www.google.org"));
	   System.out.println(urlVal.isValid("http://www.google.edu"));
	   System.out.println(urlVal.isValid("http://www.google.gov"));
	   
	   // valid ip tested
	   System.out.println(urlVal.isValid("https://192.168.0.1"));
	   System.out.println(urlVal.isValid("http://255.255.255.255"));

	   //valid URL w/ path tested
	   System.out.println(urlVal.isValid("https://en.wikipedia.org/wiki/URL"));
	   System.out.println(urlVal.isValid("http://www.google.com/test"));
	   System.out.println(urlVal.isValid("http://www.google.com/test/../../../"));
	   System.out.println(urlVal.isValid("https://tools.ietf.org/html/rfc3986#section-3.1"));

	   //Query Test
	   System.out.println(urlVal.isValid("http://www.google.com?test=query"));
	   System.out.println(urlVal.isValid("http://www.google.com:90/test/path?test=query"));
	   
	   //Port Test
	   System.out.println(urlVal.isValid("http://www.google.com:0"));
	   System.out.println(urlVal.isValid("http://www.google.com:65535"));
	   System.out.println(urlVal.isValid("http://www.google.com:999"));
	   System.out.println(urlVal.isValid("http://www.google.com:1000"));

	   //INVALID URLS
	   System.out.println("-------| BELOW SHOULD RETURN FALSE |--------");
	   System.out.println(urlVal.isValid("www.google.com"));
	   System.out.println(urlVal.isValid("http://256.255.255.255"));
	   System.out.println(urlVal.isValid("http://-111.-111.-111-111"));

	   System.out.println(urlVal.isValid("http://www.google.com:abcd"));
	   System.out.println(urlVal.isValid("bloop"));
	   System.out.println(urlVal.isValid(""));
	   System.out.println(urlVal.isValid("http:///www.google.com:abcd"));
	   System.out.println(urlVal.isValid("http://www.google.com:-1"));
	   System.out.println(urlVal.isValid("."));
	   System.out.println(urlVal.isValid("http://www.google.com/...."));
	   System.out.println(urlVal.isValid("http://www.google.com/#")); //this one taken from original test
	   System.out.println(urlVal.isValid("http://www.google.com#")); //this one taken from original test
	   System.out.println(urlVal.isValid(".://www.google.com"));
	   System.out.println(urlVal.isValid("http://www.google.com//nope"));
	   System.out.println(urlVal.isValid("http://www.google..com"));
	   System.out.println(urlVal.isValid(" .com"));
	   System.out.println(urlVal.isValid("255.com:3000/$23"));

	   
	   
	   UrlValidator httpVal = new UrlValidator(new String[] {"http"});
	   System.out.println("--------TESTING HTTP AS ONLY VALID SCHEME -----------");
	   System.out.println("-----BELOW SHOULD RETURN FALSE-----");
	   System.out.println(httpVal.isValid("totallyInval://www.google.com"));
	   System.out.println(httpVal.isValid("https://www.google.com"));
	   System.out.println(urlVal.isValid("ftp://www.amazon.com"));

	   System.out.println("-----BELOW SHOULD RETURN TRUE-----");
	   System.out.println(httpVal.isValid("http://www.google.com"));

	   
	   
	   
   }


////
   // 					Partition Testing
////


// Auth

   public String[] validAuthorityPartition = { "google.com", "255.255.255.255", "www.google.ru" };
   public String[] invalidAuthorityPartition = { " ", "256.255.255.255", "0.0.0" };
   public String[][] authorityPartition = { validAuthorityPartition, invalidAuthorityPartition };

// Path

   public String[] validPathPartition = { "/test", "/testing-123/" };
   public String[] invalidPathPartition = { " ", "e/" };
   public String[][] pathPartition = { validPathPartition, invalidPathPartition };

// Query

   public String[] validQueryPartition = { " ", "?test=123" };
   public String[] invalidQueryPartition = { "?test[]", "test=12" };
   public String[][] queryPartition = { validQueryPartition, invalidQueryPartition };
   public String[] validSchemePartition = { "http://", "https://", "ftp://" };
   public String[] invalidSchemePartition = { "htt://", "http//", " " };
   public String[][] schemePartition = { validSchemePartition, invalidSchemePartition };

 // Combo

   public String[][][] domainPartitions = { schemePartition, authorityPartition, pathPartition, queryPartition };

   
  
   public void testDomainPartitions()
   {

	   String[] partitionUnderTest;
	   String[] urlToTest = new String[4];							// [ scheme, domain, path, query ];
	   String[] passed = new String[1000];		// Passed urls.
	   String[] failed = new String[1000];		// Failed urls.
	   int numPass = 0, numFail = 0;			// Iterators on pass/fails.
	   int numLoopsThroughPart = 10;

	   for(int z = 0; z < 100; z++) {

		   for(int i = 0; i < domainPartitions.length; i++)			  		// Loop through each domain partition.
		   {
			  for(int j = 0; j < domainPartitions[i][1].length; j++) 		// Loop through invalid partition values.
			  {
				  urlToTest[i] = domainPartitions[i][1][j];				// Place current invalid value into url to test.

				  for(int k = 0; k < domainPartitions.length; k++)			// Fill in rest of url with valid values from other partitions.
				  {
					  if(k == i)		// don't override our invalid value we are testing.
						  continue;

					  urlToTest[k] = domainPartitions[k][0][(int)(Math.random() * domainPartitions[k][0].length)];		// Pick and random valid value.

				  }

				  UrlValidator validator = new UrlValidator();
				  String url = "";

				  // Convert our array of strings to a string.
				  for(int l = 0; l < urlToTest.length; l++) {
					  url += urlToTest[l];
				  }

			      boolean urlValid = validator.isValid(url);

			      if ( urlValid ) {
			        passed[numPass] = url;  // save the failed url
			        numPass++;              // increment the counter
			      } else {
			    	failed[numFail] = url;
			    	numFail++;
			      }

			  }
		   }

		   numLoopsThroughPart--;

	   }	

	  

	 // Show result


	   System.out.println(">> PASS <<\n");
	   int m = 0;
	   int n = 0;
	   while(passed[m] != null)
	   {
		   System.out.println("PASS:  " + passed[m]);
		   m++;
	   }
	   System.out.println(">> FAIL >>\n");
	   while(failed[n] != null)
	   {
		   System.out.println("FAIL: " + failed[n]);
		   n++;
	   }

   }

	  
   
   
   public void testIsValid()
   {

   	 int length = 10000;         
     int bugCount = 0;              
     int r = 0;                

     // store fail urls 

     String[] failed = new String[length];

    // Valid URL data. 
     String[] schemes    = { "http://", "", "ftp://", "h3t://" }; 
     String[] authority  = { "www.google.com", "google.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255", "255.com", "go.cc" }; 
     String[] ports      = { ":80", ":90", ":100", ":3000", ":8888" }; 
     String[] path       = { "/test", "/t123", "/$23", "/test/", "/test/next" }; 
     String[] options    = { "/test1", "/t123", "/$23", "/test/", "/$23/file" };
     String[] queries    = { "?action=view", "?action=edit&mode=down", "", "?set=true&bob=dylan&you=true" }; 

     for(int i = 0; i<length; i++)
	   {
      int scheme_index    = (int) (Math.random() * 3);
      int authority_index = (int) (Math.random() * 7);
      int ports_index     = (int) (Math.random() * 4);
      int path_index      = (int) (Math.random() * 4);
      int options_index   = (int) (Math.random() * 4);
      int queries_index   = (int) (Math.random() * 3);

//       Create a random string made up of valid url pieces 
      String url = schemes[scheme_index] + authority[authority_index] + ports[ports_index] + path[path_index] + queries[queries_index];
      UrlValidator validator =  new UrlValidator();
      boolean test = validator.isValid(url);

      if ( test == false ) {
        bugCount++;           // increase number of bugCount
        failed[r] = url;  // save the failed url
        r++;              // increment the counter
      }
     } 

  

  // Show results 

     System.out.println("Valid Url =  " + bugCount + " bugs. \n");
     System.out.println("Failed Valid Urls: \n");
     for ( int i=0; i< failed.length; i++) {
       if ( failed[i] != null ) System.out.println( i + " : " + failed[i] + "\n");
     }

     System.out.println("Valid Url Tests Complete");
//	  Test Invalid Urls 
     bugCount = 0;
     r = 0;
  

  	// holds invalid URLs that pass 

     String[] passed = new String[length];

    // Invalid URL data


     String[] badSchemes 	= { "3ht://", "http:", "http:/", "://", "http/" };
     String[] badAuthority 	= { "www.google.1com", "256.256.256.256", "16.16.16.16.16", "55.55.55", ".255.255.255.255", "192.68.102.10.", "abc", "abc.123" };
     String[] badPorts 		= { ":-1", ":8888a", ":70000", "22000" };
     String[] badPath 		= { "/..", "/../", "/path/to//file", "//#" };
     String[] badOptions 	= { "/../", "/#", "/test//file" };

   
   // Create URL, with one invalid segment 


     for(int i = 0; i < length; i++)
	 {
    
// Make valid 

         int scheme_index    = (int) (Math.random() * 3);
         int authority_index = (int) (Math.random() * 7);
         int ports_index     = (int) (Math.random() * 4);
         int path_index      = (int) (Math.random() * 4);
         int options_index   = (int) (Math.random() * 4);
         int queries_index   = (int) (Math.random() * 3);

// Replace one valid with inval

		 int bad_scheme_index 		= (int) (Math.random() * 4);
		 int bad_authority_index 	= (int) (Math.random() * 7);
		 int bad_ports_index     	= (int) (Math.random() * 3);
		 int bad_path_index      	= (int) (Math.random() * 3);
		 int bad_options_index   	= (int) (Math.random() * 2);
		 int bad_queries_index   	= (int) (Math.random() * 3);
	     int replace_piece		= (int) (Math.random() * 3);

	     String url;
	     if ( replace_piece == 0 )		
	     {
	         url = badSchemes[bad_scheme_index] + authority[authority_index] + ports[ports_index] + path[path_index] + queries[queries_index];
	     }
	     else if( replace_piece == 1 )	
	     {
	    	 url = schemes[scheme_index] + badAuthority[bad_authority_index] + ports[ports_index] + path[path_index] + queries[queries_index];
	     }
	     else if( replace_piece == 2)	
	     {
	    	 url = schemes[scheme_index] + authority[authority_index] + badPorts[bad_ports_index] + path[path_index] + queries[queries_index];
	     }
	     else							
	     {
	    	 url = schemes[scheme_index] + authority[authority_index] + ports[ports_index] + badPath[bad_path_index] + queries[queries_index];
	     }

	  

         UrlValidator validator =  new UrlValidator();
         boolean test = validator.isValid(url);
         if ( test == true ) {
             bugCount++;          
             passed[r] = url;  
             r++;              
         }
	 }	

    
    // Show bug results


     System.out.println("Invalid Url = " + bugCount + " bugs. \n");
     System.out.println("Wrong Urls Passed =  \n");
     for ( int i=0; i< failed.length; i++) {
       if ( passed[i] != null ) System.out.println( i + " : " + passed[i] + "\n");
     }

   } 
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
