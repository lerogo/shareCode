public class Test {

	public static void main(String[] args) {
		System.out.println(isSubString("The", "The cat in the hat."));
		System.out.println(isSubString("bat", "The cat in the hat."));
	}

	public static boolean isSubString(String s, String sub) {
		try {
			int len1 = s.length(), len2 = sub.length();
			for (int i = 0; i < len2; ++i) {
				for (int j = 0; j < len1; ++j) {
					if (i + j >= len2) {
						return false;
					}
					if (s.charAt(j) != sub.charAt(i + j)) {
						break;
					}
					if (j == len1 - 1) {
						return true;
					}
				}
			}
			return false;
		} catch (Exception e) {
			throw e;
		}
	}
}
