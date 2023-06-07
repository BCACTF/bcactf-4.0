#!sage
from Crypto.Util.number import *
n = 773147647777254333151152339551822957730368459394541078867788999939997137960719497653735611366001374598753493224018377217253356324543168150748430725794420474538773121418528572902389199601880952254344968810038623244653605361476288677344751093557018426767479831083267208914729835646630005527250244943764332000205876478228737786024019964680624328482688178837338414348130942611097569023557345571992137379102312710275130520889290376346192406100000850473885760093663328870550524469263765341154882587088809568183699155782834732581730769928276374237911090503047757196739272081098716052631222070371980289711373658428258958449964353752510754674815608009231587506666317509429646233077111948930354856378388970604797835704925599922352068904740378459907012278264474290766966120449667655213506851261407865729143919921492223294096378999376395711210770132793717935589785446474030561305556301687742518761800514806262345505788930433485610856218948793330900859583033987845213490446736456705023166291641562523005301995927508645522739842740854856650066246192926324050922673190271034423873351852778294676576287748762839292402372811923462709305308867489360766737655827184261660314658229658663637191140461261006130002968667304343988938284529145194941014249643
e = 65537
c = 764924069305316558096794479583468600898343650405501593837506661524669890267063929047479671075785671245350113207841816097034602794699198827682536595152727048566630492493173384599008487779604991003443958394260418432325241773495490283713629699004746923516406055233578458566510788164806385436650760814581259841112218453306352404388437344128872241079086079842518028821004711909914042552243491276488787946448151546619158254982909876561601384574028530897715726366382967953478730929831960158766204226732107877869102155597198132786928145277842679058800935522916383156630837703856182648549274678409483440145141296750547625810542188637744664412262802989125272920575892348528063580880485809202830484046724836473431341190900150600200147020032762042149788555885570568068758783672647565830752998888532805483843684683661153257349102310347144121320420234292677923054288878517908522046046867717545306062502624832083185383950748346424915791642173140082694822774636392472969638734192675966632116084093963739417598371295730223889125590783891094330908920331936693434306479832578221950773577959629885762448795152003128632753008451693737629500490634113290673603046049483205366779909086277333800738407966505169774697452080792423162675250220999163540992106509

# Suppose p = a^2+k and q = b^2+l, where |k|, |l| <= 10
# Then n = pq = (ab)^2 + la^2 + kb^2 + kl. WLOG a > b
# Note that a and b will be easier to factor than n since
# they will likely not be semiprimes. Since a and b have
# the same bit length, a < 2b, and |la^2+kb^2|<10(a^2+b^2)
# = 10ab(a/b + b/a) < 25ab. kl is negligible so we can
# guarantee that |ab-sqrt(n)| < 13 (see e.g. (ab+13)^2 = 
# (ab)^2 + 26ab + 169).
# For each guess of (ab, k, l) (of which there are on the
# order of 10^3 possibilities), let d=ab for convenience.
# Then d^2 + la^2 + kd^2/a^2 + kl = n
# l(a^2)^2 + (d^2+kl-n)(a^2) + kd^2 = 0.
# This is a simple quadratic that lets us solve for a^2 in
# constant time. 
p = 0
q = 0
def check(a2,d,k,l):
    global p, q
    if sqrt(a2).is_integer() and (d/sqrt(a2)).is_integer():
        p_temp = a2+k
        q_temp = d^2/a2 + l
        if is_prime(ZZ(p_temp)) and is_prime(ZZ(q_temp)): # UserWarning: Testing primality in Rational Field, which is a field, hence the result will always be False. To test whether n is a prime integer, use is_prime(ZZ(n)) or ZZ(n).is_prime(). Using n.is_prime() instead will silence this warning.
            print(f'a = {sqrt(a2)}')
            print(f'b = {d/sqrt(a2)}')
            print(f'p = {p_temp}')
            print(f'q = {q_temp}')
            p = p_temp
            q = q_temp


rt = round(sqrt(n))
for d in range(rt-13, rt+14):
    for k in range(-10, 11):
        for l in range(-10, 11):
            if k == 0 or l == 0:
                continue
            if p != 0: # found already
                break
            print(f'Trying (d*,k,l) = {d-round(sqrt(n))}, {k}, {l}')
            b = d^2 + k*l - n
            check((-b + sqrt(b^2 - 4*l*k*d^2)) / (2*l),d,k,l)
            check((-b - sqrt(b^2 - 4*l*k*d^2)) / (2*l),d,k,l)
            
print(p)
print(q)

#Now it's normal RSA
s = pow(e, -1, lcm(p-1, q-1))
m = pow(c, s, n)
print(long_to_bytes(m))