/**
 *  MicroEmulator
 *  Copyright (C) 2006-2007 Bartek Teodorczyk <barteo@barteo.net>
 *  Copyright (C) 2006-2007 Vlad Skarzhevskyy
 *
 *  It is licensed under the following two licenses as alternatives:
 *    1. GNU Lesser General Public License (the "LGPL") version 2.1 or any newer version
 *    2. Apache License (the "AL") Version 2.0
 *
 *  You may not use this file except in compliance with at least one of
 *  the above two licenses.
 *
 *  You may obtain a copy of the LGPL at
 *      http://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
 *
 *  You may obtain a copy of the AL at
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the LGPL or the AL for the specific language governing permissions and
 *  limitations.
 *
 *  @version $Id: CLDC11APIDeclarationsTest.java 1643 2008-03-05 06:40:37Z vlads $
 */
package test;

import net.sf.jour.signature.APICompareConfig;
import net.sf.jour.signature.SignatureTestCase;

/**
 * @author vlads
 * 
 */
public class CLDC11APIDeclarationsTest extends SignatureTestCase {

	public String getAPIPath() {
		return "./target/classes";
	}

	public boolean isUeSystemClassPath() {
		return false;
	}

	public APICompareConfig getAPICompareConfig() {
		APICompareConfig c = new APICompareConfig();
		// c.setCompareLevelPackage();
		return c;
	}

	public String getSignatureXMLPath() {
		return "cldcapi11-signature.xml";
	}

}
