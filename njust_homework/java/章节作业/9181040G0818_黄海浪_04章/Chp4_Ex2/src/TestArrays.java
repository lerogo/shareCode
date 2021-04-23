public class TestArrays {
	public static void printArray(int[] array) {
		System.out.print('<');
		for (int i = 0; i < array.length; i++) {
			System.out.print(array[i]);
			if ((i + 1) < array.length) {
				System.out.print(",");
			}
		}
		System.out.print('>');
	}

	public static void main(String[] args) {
		int[] arr1 = { 2, 3, 5, 7, 11, 13, 17, 19 };
		int[] arr2;
		System.out.print("array1 is ");
		printArray(arr1);
		System.out.println();
		arr2 = arr1;
		arr2[0] = 0;
		arr2[2] = 2;
		arr2[4] = 4;
		arr2[6] = 6;
		System.out.print("array1 is ");
		printArray(arr1);
		System.out.println();
	}
}