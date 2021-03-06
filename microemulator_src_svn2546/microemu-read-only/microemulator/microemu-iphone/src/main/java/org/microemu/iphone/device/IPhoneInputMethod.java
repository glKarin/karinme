/**
 *  MicroEmulator
 *  Copyright (C) 2008 Markus Heberling <markus@heberling.net>
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
 *  @version $Id: IPhoneInputMethod.java 1896 2009-01-07 14:26:05Z tisoft $
 */
package org.microemu.iphone.device;

import org.microemu.device.InputMethod;

public class IPhoneInputMethod extends InputMethod{

	@Override
	public void dispose() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public int getGameAction(int keyCode) {
		// TODO currently one-to-one mapping which is wrong
		return keyCode;
	}

	@Override
	public int getKeyCode(int gameAction) {
		// TODO currently one-to-one mapping which is wrong
		return gameAction;
	}

	@Override
	public String getKeyName(int keyCode) throws IllegalArgumentException {
		return String.valueOf((char)keyCode);
	}

}
