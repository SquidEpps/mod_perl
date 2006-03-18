/* Copyright 2001-2006 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

static MP_INLINE
SV *mpxs_Apache2__Connection_pnotes(pTHX_ conn_rec *c, SV *key, SV *val)
{
    MP_dCCFG;

    modperl_config_con_init(c, ccfg);
    
    if (!ccfg) {
        return &PL_sv_undef;
    }
    
    return modperl_pnotes(aTHX_ &ccfg->pnotes, key, val, NULL, c);
}
