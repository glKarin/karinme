/**
 *  MicroEmulator
 *  Copyright (C) 2001-2007 Bartek Teodorczyk <barteo@barteo.net>
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
 *  @version $Id: NewJSRFacade.java 1605 2008-02-25 21:07:14Z barteo $
 */
package javax.microedition.io.newjsr;

/**
 * @author vlads
 *
 * To test if MIDlet can override javax.microedition package on the device.
 */
public class NewJSRFacade {

	private static class WorkerImpl implements NewJSRInterface {

		public String doStuff(String data) {
			System.out.println("Working on " + data);
			return data;
		}
		
	}
	
	public static NewJSRInterface createWorker() {
		return new WorkerImpl();
	}
	
}
